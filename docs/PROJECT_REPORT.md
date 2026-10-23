# RentEase: Vehicle Rental Management Web Application Using SOLID Principles

**Course:** Object-Oriented Programming  
**Project type:** Mini Project  
**Language:** C++17  
**Frontend:** HTML, the standard web markup language, CSS, the web styling language, and JavaScript  
**Project title:** RentEase, SOLID Vehicle Rental Web App  
**Team members:** __________________________ and __________________________  
**Registration numbers:** __________________________

## 1. Abstract
How about this, RentEase is a small web-based vehicle rental management application devised to show object-oriented programming and the five SOLID design principles, at least in practice, and together, a browser-based interface is making the process easier to show, and the C++ backend handles validation, price calculation, availability and rental entries, to a significant degree. Interfaces and separate classes are being employed by the project so that new vehicle types, pricing policies, payment methods, and notification channels can (to a meaningful extent) be added with slight changes to existing code. Users can (at least in most settings) view a list of cars and bikes, choose an available vehicle, enter a customer name and rental duration, pick a copied payment method, and receive a booking confirmation.

## 2. Problem Statement
What's more, a clear way is being needed by small rental businesses to show available vehicles, find rental charges, record bookings, and validate reservations, in actual application. User interface, pricing, payments, and booking logic in one large class are often mixed by a poorly structured program, at least in principle. Such code becomes difficult to uphold and generalize, and rentEase is tackling this design problem, through the modular object-oriented code organized around SOLID principles.

## 3. Objectives
1. Build a working local web application with a C++ backend.
2. Demonstrate encapsulation, abstraction, inheritance and polymorphism.
3. Show concrete examples of SRP, OCP, LSP, ISP and DIP.
4. Validate customer input, rental duration, and vehicle availability.
5. Find rental totals and simulate payment and confirmation.
6. Generate a project that two students can (in practice) show and explain in a viva.

## 4. Scope and Real-Life Application
Sure enough, the application models a simplified vehicle rental counter. A real business could broaden this design with a database, user authentication, actual payment gateway, driving-license verification, rental return workflow, late fees, and email/SMS notifications. These production features are intentionally outside the scope of this beginner-friendly mini-project, on the whole. A customer chooses a car or bike and specifies how many days it's needed. This setup is checking availability, finds the cost, entries a booking, and shows a confirmation, in real-world scenarios.

## 5. Technology Stack
- C++17: business logic and HTTP server.
- HTML: page structure and booking form.
- CSS: responsive visual design.
- JavaScript Fetch API: communicates with the C++ backend.
- POSIX sockets: receives local HTTP requests without third-party C++ libraries.
- In-memory vectors: stores vehicles and current-session rental data.

## 6. System Design
The server routes requests to the `RentalService` abstraction. So, each responsibility is set aside to a separate class or interface, all things considered. Honestly, HTTP requests to the C++ server are sent by the browser. In turn, the service coordinates vehicle availability, pricing, payment, rental record creation, and notifications, in the main.

**Main flow:**
1. Browser requests `GET /api/vehicles`.
2. Vehicle details and availability are, after all, returned as JSON, a standard data exchange format, by c++, in many respects.
3. User turns in the booking form.
4. Browser sends `POST /api/rentals`.
5. Input and checks availability is being validated by service.
6. A pricing strategy finds the total.
7. Payment is being imitated by a payment implementation.
8. The vehicle is marked unavailable and a rental record is created.
9. Notification service prints a confirmation in Terminal and the browser shows the finding.

## 7. Main Classes
| Class / Interface | Responsibility |
|---|---|
| `Vehicle` | Abstract contract for vehicle data and availability |
| `Car`, `Bike` | Concrete vehicle types |
| `PricingStrategy` | Common price-calculation contract |
| `StandardPricing` | Daily rate multiplied by days |
| `WeeklyDiscountPricing` | Example alternative with 10% discount for 7+ days |
| `PaymentMethod` | Common payment contract |
| `CashPayment`, `UpiPayment` | Simulated payment implementations |
| `NotificationService` | Notification contract |
| `ConsoleNotification` | Prints booking confirmation to Terminal |
| `RentalService` | Booking use-case contract |
| `DefaultRentalService` | Validates and coordinates booking operations |
| `HttpServer` | Handles HTTP and serves the frontend |

## 8. Implementation of SOLID Principles

### 8.1 Single Responsibility Principle (SRP)
Like, `HttpServer` handles networking, `DefaultRentalService` manages the booking workflow, and `ConsoleNotification` handles notification output, at least empirically. A concentrated responsibility is had by each class. In turn, a change to the web request format doesn't need rewriting the vehicle classes, broadly speaking.

### 8.2 Open/Closed Principle (OCP)
The `PricingStrategy` interface is making price calculation extensible. `StandardPricing` and `WeeklyDiscountPricing` are implementing the same contract. A developer can add a new approach, such as a holiday discount, without changing the interface or rewriting the booking workflow.

### 8.3 Liskov Substitution Principle (LSP)
The `Vehicle` contract is being implemented by both `Car` and `Bike`. Indeed, the service is storing them as `shared_ptr<Vehicle>` and employs their typical methods, so either type can, to some extent, be replaced wherever a `Vehicle` is anticipated, at least for now.

### 8.4 Interface Segregation Principle (ISP)
The program employs small interfaces: `PaymentMethod`, `NotificationService`, and `PricingStrategy`. So, a payment class isn't needed to use notification or price-calculation methods, broadly speaking. Each exposes only the operations pertinent to that responsibility.

### 8.5 Dependency Inversion Principle (DIP)
Pricing and notification abstractions are received, through its constructor by the high-level booking service, broadly speaking. Indeed, concrete choices are created in `main.cpp`, which acts as the composition root, so this is decreasing tight coupling and makes implementations easier to replace, at least in principle. The `RentalService` interface is being employed by the HTTP server.

## 9. Core OOP Concepts
- Encapsulation: Put it like this it's, private data members in `Car` and `Bike`, accessed, through the public methods, on the whole.
- Abstraction: abstract base classes specify contracts while hiding implementation details.
- Inheritance: `Car` and `Bike` derive from `Vehicle`.
- Polymorphism: virtual methods are allowing distinct concrete objects to be employed, through a prevalent interface, to a significant degree.
- Composition: the rental service collaborates with pricing, payment, and notification objects.

## 10. Validation and Testing
Suggested demonstration tests:
1. Valid customer + available vehicle + 2 days, such as booking succeeds and total equals daily rate × 2, in actual application.
2. Empty customer name, such as booking is mainly rejected.
3. Days set to 0 or greater than 30 - booking is rejected.
4. Invalid vehicle ID, including booking is often rejected.
5. Book a vehicle once and attempt to book it again: second booking is generally rejected, because the vehicle is usually unavailable, all things considered.
6. Choose Cash, namely confirmation is saying cash was recorded as a demo.
7. Choose UPI, such as confirmation clearly is saying no real money was transferred.
8. Check recent bookings, including the successful rental is appearing in the table.

## 11. Limitations
The project is designed for local classroom demonstration. So, payment is copied, there's no authentication or database, on the whole. Data is kept in memory and is lost when the server stops. In turn, as well, the slight HTTP server isn't designed for public internet deployment. These shortcomings are keeping the mini-project centered on the needed design principles rather than infrastructure, in the main.

## 12. Future Enhancements
- In SQLite/MySQL, store vehicles and bookings.
- Add login and role-based access for customer and admin.
- Add rental return, late fee, and vehicle maintenance modules.
- In a secure environment, add actual payment gateway integration.
- Add email/SMS notification adapters.
- Add automated unit tests and booking history persistence.

## 13. Conclusion
RentEase shows how SOLID principles can (at least in theory) raise the architecture of a practical application. In turn, plus, hTTP handling is making the code easier to understand and expand, at least in practice. Separating vehicles, pricing, payments, notifications, booking logic. The browser interface visibly is showing. Together, the coring object-oriented design is shown by the C++ backend. The project is meeting its educational goal by connecting each SOLID principle to a concrete code, on the whole.

## 14. References
1. Course notes on Object-Oriented Programming and SOLID principles.
2. C++ language reference for classes, inheritance, virtual functions, and smart pointers.
3. MDN Web Docs for HTML forms, CSS, JavaScript Fetch API, and HTTP concepts.
