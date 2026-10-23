#pragma once
#include "rental_service.hpp"
#include <string>

class HttpServer {
    RentalService& service_;
    int port_;
public:
    HttpServer(RentalService& service, int port);
    void run();
private:
    std::string route(const std::string& method, const std::string& path,
                      const std::string& body, std::string& contentType);
};
