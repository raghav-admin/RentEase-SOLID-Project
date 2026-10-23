#pragma once
#include <algorithm>

class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual int calculate(int dailyRate, int days) const = 0;
};

// Standard pricing: daily rate multiplied by rental days.
class StandardPricing final : public PricingStrategy {
public:
    int calculate(int dailyRate, int days) const override {
        return dailyRate * days;
    }
};

// Add another approach without editing RentalService: this is the Open/Closed Principle in practice. Longer rentals receive a 10% discount.
class WeeklyDiscountPricing final : public PricingStrategy {
public:
    int calculate(int dailyRate, int days) const override {
        const int subtotal = dailyRate * days;
        return days >= 7 ? subtotal * 90 / 100 : subtotal;
    }
};
