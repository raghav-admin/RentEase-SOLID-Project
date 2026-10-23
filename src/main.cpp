#include "http_server.hpp"
#include "pricing.hpp"
#include "rental_service.hpp"
#include "services.hpp"
#include <iostream>
#include <memory>

int main() {
    // Composition root: concrete objects are created here and injected.
    auto pricing = std::make_shared<StandardPricing>();
    auto notifier = std::make_shared<ConsoleNotification>();
    DefaultRentalService rentalService(pricing, notifier);
    HttpServer server(rentalService, 8080);

    std::cout << "RentEase is running at http://localhost:8080\n";
    std::cout << "Press Ctrl+C to stop the server.\n";
    server.run();
    return 0;
}
