#include "rental_service.hpp"
#include <algorithm>
#include <cctype>
#include <utility>

DefaultRentalService::DefaultRentalService(
    std::shared_ptr<PricingStrategy> pricing,
    std::shared_ptr<NotificationService> notifier)
    : pricing_(std::move(pricing)), notifier_(std::move(notifier)) {
    vehicles_.push_back(std::make_shared<Car>(1, "Honda City", 1500));
    vehicles_.push_back(std::make_shared<Car>(2, "Hyundai i20", 1200));
    vehicles_.push_back(std::make_shared<Bike>(3, "Royal Enfield Classic", 700));
    vehicles_.push_back(std::make_shared<Bike>(4, "Honda Activa", 400));
}

std::vector<std::shared_ptr<Vehicle>> DefaultRentalService::vehicles() const {
    return vehicles_;
}

const std::vector<RentalRecord>& DefaultRentalService::rentals() const {
    return rentals_;
}

BookingResult DefaultRentalService::book(const std::string& customer, int vehicleId,
                                          int days, const std::string& paymentType) {
    if (customer.empty()) return {false, "Please enter the customer's name.", 0, 0};
    if (days < 1 || days > 30) return {false, "Rental days must be between 1 and 30.", 0, 0};

    auto it = std::find_if(vehicles_.begin(), vehicles_.end(),
        [vehicleId](const auto& vehicle) { return vehicle->id() == vehicleId; });
    if (it == vehicles_.end()) return {false, "Vehicle not found.", 0, 0};
    if (!(*it)->available()) return {false, "This vehicle is already rented.", 0, 0};

    std::shared_ptr<PaymentMethod> payment;
    if (paymentType == "upi") payment = std::make_shared<UpiPayment>();
    else if (paymentType == "cash") payment = std::make_shared<CashPayment>();
    else return {false, "Choose Cash or UPI payment.", 0, 0};

    const int total = pricing_->calculate((*it)->dailyRate(), days);
    std::string paymentMessage;
    if (!payment->pay(total, paymentMessage))
        return {false, "Payment could not be processed.", 0, 0};

    (*it)->setAvailable(false);
    const int id = nextRentalId_++;
    rentals_.push_back({id, customer, (*it)->id(), (*it)->name(),
                        (*it)->type(), days, total, paymentType});
    const std::string message = "Booking #" + std::to_string(id) + " confirmed for " +
        (*it)->name() + " (" + std::to_string(days) + " day(s)). " + paymentMessage;
    notifier_->send(customer, message);
    return {true, message, total, id};
}
