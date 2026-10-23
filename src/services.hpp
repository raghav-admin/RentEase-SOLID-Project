#pragma once
#include <iostream>
#include <string>

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual bool pay(int amount, std::string& message) = 0;
};

class CashPayment final : public PaymentMethod {
public:
    bool pay(int amount, std::string& message) override {
        message = "Cash payment recorded (demo only): Rs. " + std::to_string(amount);
        return true;
    }
};

class UpiPayment final : public PaymentMethod {
public:
    bool pay(int amount, std::string& message) override {
        message = "UPI payment simulated (no money transferred): Rs. " + std::to_string(amount);
        return true;
    }
};

class NotificationService {
public:
    virtual ~NotificationService() = default;
    virtual void send(const std::string& customer, const std::string& message) = 0;
};

class ConsoleNotification final : public NotificationService {
public:
    void send(const std::string& customer, const std::string& message) override {
        std::cout << "[Notification to " << customer << "] " << message << std::endl;
    }
};
