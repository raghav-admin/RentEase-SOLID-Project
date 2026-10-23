#include "http_server.hpp"
#include "pricing.hpp"
#include "rental_service.hpp"
#include "services.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

int main() {
    // Composition root: create concrete objects and inject dependencies.
    auto pricing = std::make_shared<StandardPricing>();
    auto notifier = std::make_shared<ConsoleNotification>();

    DefaultRentalService rentalService(pricing, notifier);

    // Use Render's assigned port when deployed; otherwise use 8080 locally.
    int port = 8080;

    if (const char* envPort = std::getenv("PORT")) {
        try {
            port = std::stoi(envPort);
        } catch (...) {
            std::cerr << "Invalid PORT value. Using port 8080.\n";
        }
    }

    HttpServer server(rentalService, port);

    std::cout << "RentEase is running on port " << port << '\n';
    std::cout << "Press Ctrl+C to stop the server.\n";

    server.run();

    return 0;
}