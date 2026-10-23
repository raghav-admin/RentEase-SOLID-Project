#pragma once
#include <string>
#include <memory>

class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual int id() const = 0;
    virtual std::string name() const = 0;
    virtual std::string type() const = 0;
    virtual int dailyRate() const = 0;
    virtual bool available() const = 0;
    virtual void setAvailable(bool value) = 0;
};

class Car final : public Vehicle {
    int id_;
    std::string name_;
    int rate_;
    bool available_ = true;
public:
    Car(int id, std::string name, int rate)
        : id_(id), name_(std::move(name)), rate_(rate) {}
    int id() const override { return id_; }
    std::string name() const override { return name_; }
    std::string type() const override { return "Car"; }
    int dailyRate() const override { return rate_; }
    bool available() const override { return available_; }
    void setAvailable(bool value) override { available_ = value; }
};

class Bike final : public Vehicle {
    int id_;
    std::string name_;
    int rate_;
    bool available_ = true;
public:
    Bike(int id, std::string name, int rate)
        : id_(id), name_(std::move(name)), rate_(rate) {}
    int id() const override { return id_; }
    std::string name() const override { return name_; }
    std::string type() const override { return "Bike"; }
    int dailyRate() const override { return rate_; }
    bool available() const override { return available_; }
    void setAvailable(bool value) override { available_ = value; }
};

struct RentalRecord {
    int rentalId;
    std::string customer;
    int vehicleId;
    std::string vehicleName;
    std::string vehicleType;
    int days;
    int total;
    std::string payment;
};
