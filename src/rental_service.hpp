#pragma once
#include "models.hpp"
#include "pricing.hpp"
#include "services.hpp"
#include <memory>
#include <string>
#include <vector>

struct BookingResult {
    bool success = false;
    std::string message;
    int total = 0;
    int rentalId = 0;
};

class RentalService {
public:
    virtual ~RentalService() = default;
    virtual std::vector<std::shared_ptr<Vehicle>> vehicles() const = 0;
    virtual const std::vector<RentalRecord>& rentals() const = 0;
    virtual BookingResult book(const std::string& customer, int vehicleId,
                               int days, const std::string& paymentType) = 0;
};

class DefaultRentalService final : public RentalService {
    std::vector<std::shared_ptr<Vehicle>> vehicles_;
    std::vector<RentalRecord> rentals_;
    std::shared_ptr<PricingStrategy> pricing_;
    std::shared_ptr<NotificationService> notifier_;
    int nextRentalId_ = 1001;
public:
    DefaultRentalService(std::shared_ptr<PricingStrategy> pricing,
                         std::shared_ptr<NotificationService> notifier);
    std::vector<std::shared_ptr<Vehicle>> vehicles() const override;
    const std::vector<RentalRecord>& rentals() const override;
    BookingResult book(const std::string& customer, int vehicleId,
                       int days, const std::string& paymentType) override;
};
