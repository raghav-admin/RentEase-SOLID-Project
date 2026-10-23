# SOLID principle map in RentEase

## 1. Single Responsibility Principle (SRP)
**Meaning:** A class should have one main reason to change.
- `Car` and `Bike` represent vehicle-specific data and behavior.
- `DefaultRentalService` coordinates the rental use case.
- `HttpServer` handles HTTP requests and responses.
- `ConsoleNotification` is responsible for sending/displaying a notification.
- `CashPayment` and `UpiPayment` each represent one payment behavior.

**Why it matters:** Changing the webpage/server protocol should not require rewriting vehicle pricing or payment behavior.

## 2. Open/Closed Principle (OCP)
**Meaning:** Software entities should be open for extension but closed for modification.
- `PricingStrategy` is an abstraction.
- `StandardPricing` and `WeeklyDiscountPricing` are separate implementations.
- A future `FestivalDiscountPricing` can be added by implementing `PricingStrategy`, without changing the calculation contract or the booking workflow.

The active strategy is selected in `src/main.cpp`. The sample app uses standard pricing so the displayed estimate and backend total match.

## 3. Liskov Substitution Principle (LSP)
**Meaning:** Any implementation of a base abstraction should be usable wherever that abstraction is expected without breaking the program.
- `Car` and `Bike` both implement `Vehicle`.
- The service stores `std::shared_ptr<Vehicle>` and uses `id()`, `name()`, `dailyRate()`, and availability methods.
- The catalogue and booking workflow do not need to know the concrete class to read these common properties.

## 4. Interface Segregation Principle (ISP)
**Meaning:** Clients should not be forced to depend on methods they do not use.
- `PaymentMethod` only exposes `pay()`.
- `NotificationService` only exposes `send()`.
- `PricingStrategy` only exposes `calculate()`.
These small interfaces avoid one large interface containing unrelated methods such as `pay`, `notify`, `calculatePrice`, `printReceipt`, and `manageVehicle`.

## 5. Dependency Inversion Principle (DIP)
**Meaning:** High-level policy should depend on abstractions, not concrete low-level details.
- `DefaultRentalService` receives a `PricingStrategy` and `NotificationService` through its constructor.
- It uses `PaymentMethod` through the interface when processing payment.
- `HttpServer` depends on the `RentalService` interface, not on `DefaultRentalService`.
- `main.cpp` creates the concrete implementations and injects them. This is a simple example of dependency injection.

## OOP concepts showed
- **Encapsulation:** Vehicle fields are private; public methods expose controlled access.
- **Abstraction:** `Vehicle`, `PricingStrategy`, `PaymentMethod`, `NotificationService`, and `RentalService` are abstract interfaces.
- **Inheritance:** `Car` and `Bike` inherit from `Vehicle`; payment implementations inherit from `PaymentMethod`.
- **Polymorphism:** Code invokes virtual methods through base-class pointers/references, and the actual implementation runs at runtime.
- **Composition:** `DefaultRentalService` holds references to abstractions it collaborates with.

## Honest restrictions to mention
- In-memory storage resets when the server stops.
- Payments are simulations only.
- This compact learning server is designed for localhost demonstration, not public production use.
- It handles one client at a time and intentionally avoids frameworks/database setup to keep the project easy to compile and explain.
