#include "http_server.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) return "<h1>Frontend file not found</h1><p>Run the server from the project root.</p>";
    std::ostringstream out; out << file.rdbuf(); return out.str();
}
std::string jsonEscape(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == '"' || c == '\\') { out += '\\'; out += c; }
        else if (c == '\n') out += "\\n";
        else if (static_cast<unsigned char>(c) >= 32) out += c;
    }
    return out;
}
std::string decode(const std::string& s) {
    std::string out;
    for (size_t i=0; i<s.size(); ++i) {
        if (s[i] == '+') out += ' ';
        else if (s[i] == '%' && i+2 < s.size()) {
            try { out += static_cast<char>(std::stoi(s.substr(i+1,2),nullptr,16)); i+=2; }
            catch (...) { out += s[i]; }
        } else out += s[i];
    }
    return out;
}
std::string param(const std::string& body, const std::string& key) {
    std::istringstream ss(body); std::string part;
    while (std::getline(ss, part, '&')) {
        auto pos = part.find('=');
        if (pos != std::string::npos && decode(part.substr(0,pos)) == key)
            return decode(part.substr(pos+1));
    }
    return "";
}
std::string vehicleJson(const std::vector<std::shared_ptr<Vehicle>>& vehicles) {
    std::ostringstream out; out << "[";
    bool first=true;
    for (const auto& v : vehicles) {
        if (!first) out << ","; first=false;
        out << "{\"id\":" << v->id() << ",\"name\":\"" << jsonEscape(v->name())
            << "\",\"type\":\"" << v->type() << "\",\"rate\":" << v->dailyRate()
            << ",\"available\":" << (v->available() ? "true" : "false") << "}";
    }
    out << "]"; return out.str();
}
std::string rentalsJson(const std::vector<RentalRecord>& rentals) {
    std::ostringstream out; out << "["; bool first=true;
    for (const auto& r : rentals) {
        if (!first) out << ","; first=false;
        out << "{\"id\":" << r.rentalId << ",\"customer\":\"" << jsonEscape(r.customer)
            << "\",\"vehicle\":\"" << jsonEscape(r.vehicleName) << "\",\"type\":\""
            << r.vehicleType << "\",\"days\":" << r.days << ",\"total\":" << r.total
            << ",\"payment\":\"" << r.payment << "\"}";
    }
    out << "]"; return out.str();
}
}

HttpServer::HttpServer(RentalService& service, int port) : service_(service), port_(port) {}

std::string HttpServer::route(const std::string& method, const std::string& path,
                              const std::string& body, std::string& contentType) {
    contentType = "application/json; charset=utf-8";
    if (method == "GET" && (path == "/" || path == "/index.html")) {
        contentType = "text/html; charset=utf-8";
        return readFile("web/index.html");
    }
    if (method == "GET" && path == "/api/vehicles") return vehicleJson(service_.vehicles());
    if (method == "GET" && path == "/api/rentals") return rentalsJson(service_.rentals());
    if (method == "POST" && path == "/api/rentals") {
        const std::string customer = param(body, "customer");
        const std::string vehicleText = param(body, "vehicleId");
        const std::string daysText = param(body, "days");
        const std::string payment = param(body, "payment");
        int vehicleId=0, days=0;
        try { vehicleId = std::stoi(vehicleText); days = std::stoi(daysText); }
        catch (...) { return "{\"success\":false,\"message\":\"Vehicle and days must be valid numbers.\"}"; }
        BookingResult result = service_.book(customer, vehicleId, days, payment);
        return std::string("{\"success\":") + (result.success ? "true" : "false") +
            ",\"message\":\"" + jsonEscape(result.message) + "\",\"total\":" +
            std::to_string(result.total) + ",\"rentalId\":" + std::to_string(result.rentalId) + "}";
    }
    contentType = "application/json; charset=utf-8";
    return "{\"error\":\"Not found\"}";
}

void HttpServer::run() {
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) { perror("socket"); return; }
    int opt=1; setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    sockaddr_in address{}; address.sin_family=AF_INET;
    address.sin_addr.s_addr=htonl(INADDR_ANY); address.sin_port=htons(port_);
    if (bind(serverFd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        perror("bind"); close(serverFd); return;
    }
    if (listen(serverFd, 10) < 0) { perror("listen"); close(serverFd); return; }
    while (true) {
        sockaddr_in client{}; socklen_t len=sizeof(client);
        int clientFd=accept(serverFd, reinterpret_cast<sockaddr*>(&client), &len);
        if (clientFd < 0) continue;
        std::string request; char buffer[4096]; ssize_t n;
        while ((n=recv(clientFd, buffer, sizeof(buffer), 0)) > 0) {
            request.append(buffer, static_cast<size_t>(n));
            auto headerEnd=request.find("\r\n\r\n");
            if (headerEnd != std::string::npos) {
                size_t contentLength=0;
                std::istringstream headers(request.substr(0,headerEnd));
                std::string line; std::getline(headers,line);
                while (std::getline(headers,line)) {
                    std::transform(line.begin(),line.end(),line.begin(),
                        [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
                    if (line.find("content-length:") == 0) {
                        try { contentLength=std::stoul(line.substr(15)); } catch (...) {}
                    }
                }
                if (request.size() >= headerEnd+4+contentLength) break;
            }
            if (request.size() > 1024*1024) break;
        }
        auto headerEnd=request.find("\r\n\r\n");
        std::string method="GET", path="/", body;
        if (headerEnd != std::string::npos) {
            std::istringstream firstLine(request.substr(0, request.find("\r\n")));
            firstLine >> method >> path;
            body=request.substr(headerEnd+4);
        }
        auto q=path.find('?'); if(q!=std::string::npos) path=path.substr(0,q);
        std::string contentType;
        std::string response=route(method,path,body,contentType);
        int status=(response.find("{\"error\"") == 0) ? 404 : 200;
        std::ostringstream head;
        head << "HTTP/1.1 " << status << (status==200 ? " OK" : " Not Found")
             << "\r\nContent-Type: " << contentType
             << "\r\nContent-Length: " << response.size()
             << "\r\nAccess-Control-Allow-Origin: *"
             << "\r\nConnection: close\r\n\r\n";
        std::string full=head.str()+response;
        size_t sent=0;
        while(sent<full.size()) {
            ssize_t count=send(clientFd,full.data()+sent,full.size()-sent,0);
            if(count<=0) break; sent+=static_cast<size_t>(count);
        }
        close(clientFd);
    }
    close(serverFd);
}
