# RentEase Viva Preparation (Easy English / Hinglish)

## 30-second introduction
"Good morning. Our project is RentEase, a vehicle rental web application. We built the backend in C++17 and the frontend using HTML, CSS and JavaScript. A user can select a car or bike, enter rental days, choose a simulated payment method and get a booking confirmation. The main objective is to demonstrate OOP concepts and all five SOLID principles through separate classes and interfaces."

## Common viva questions

### 1. What problem does your project solve?
It models the basic rental-counter workflow: display vehicles, check availability, calculate rent, record a booking, and confirm it.

### 2. Why did you choose C++?
And C++ is supporting classes, inheritance, abstract classes, virtual functions, encapsulation and polymorphism, which are currently central to our OOP and SOLID demonstration, to a significant degree.

### 3. What is SOLID?
How about this, SOLID is a set of five object-oriented design principles that are helping make software easier to sustain, test and generalize, including SRP, OCP, LSP, ISP, and DIP, all things considered.

### 4. Explain SRP in your code.
My point is, Single Responsibility Principle means one class should probably have one central responsibility. In Hinglish: har class ka ek stressed kaam hai, and `HttpServer` handles HTTP requests, `DefaultRentalService` handles booking workflow, and `ConsoleNotification` handles notification output.

### 5. Explain OCP.
Bluntly, open/Closed Principle means code should be open for extension but closed for revision, in the main. `PricingStrategy` is allowing new pricing rules to be added as new classes, such as weekly or festival discount, without rewriting the rental service, at least empirically.

### 6. Explain LSP.
`Car` Liskov Substitution Principle means child implementations should work wherever the parent abstraction is anticipated, broadly speaking, and `Bike` both follow the `Vehicle` contract, so the service can use either, through a `Vehicle` pointer, in real-world scenarios.

### 7. Explain ISP.
`PaymentMethod` only has `pay()`. While `NotificationService` only has `send()`, so Interface Segregation Principle means small, centered interfaces are often better than one large interface, in actual application.

### 8. Explain DIP.
Dependency Inversion Principle means high-level logic should likely rest on abstractions, not fixed concrete classes, on the whole. `PricingStrategy` and `NotificationService` are received in its constructor by `DefaultRentalService`. `HttpServer` rests on the `RentalService` interface.

### 9. What is abstraction?
Abstraction exposes what an object can maybe do while hiding implementation details, and to show, `PaymentMethod` exposes `pay()` without forcing the booking service to know the internal details of Cash or UPI, at least in principle.

### 10. What is encapsulation?
Vehicle fields are, after all, private and accessed through the public methods. In turn, keeping data and related operations together and controlling access.

### 11. What is inheritance?
`Car` A class is working out from another class and reuses/implements its contract, and `Bike` inherit from `Vehicle`.

### 12. What is polymorphism?
The same interface call can, after all, perform diverse implementations. And thus, calling `type()` through a `Vehicle` pointer returns "Car" or "Bike" resting on the actual object, at least for now.

### 13. Why are functions virtual?
The code matching the actual object is usually called, through a base-class pointer or reference, all things considered. Runtime polymorphism is being allowed by virtual functions.

### 14. Why use `shared_ptr`?
It's a C++ smart pointer that's helping manage object lifetime automatically. Indeed, here vehicle objects are, as a matter of fact, stored through the prevalent `Vehicle` abstraction, on the whole.

### 15. How is the rental cost calculated?
For standard pricing: `total = dailyRate * days`. A separate weekly approach is showing how another policy can (at least in most settings) be added, so to make, a car at ₹1,500/day for 2 days costs ₹3,000, on the whole.

### 16. Does UPI make a real payment?
No. It's a modelling for the mini-project. So, the app obviously is saying no money is normally transferred, at least in practice.

### 17. Where is the data stored?
In vectors in memory. This is keeping the project uncomplicated, but data resets when the server stops. And thus, a database could be added later.

### 18. How does the frontend talk to C++?
The C++ server returns JSON, a standard data exchange format, which the frontend is showing, so not only that, javaScript is employing the Fetch API to send HTTP requests to `localhost:8080`, broadly speaking.

### 19. What happens if the vehicle is already rented?
The service is checking its availability and rejects a second booking for the same vehicle, in many respects.

### 20. What would you improve?
Database persistence, authentication, actual secure payment integration, return/late-fee workflow, and automated tests.

## Useful code locations
- `src/models.hpp`: Vehicle, Car, Bike, inheritance and LSP.
- `src/pricing.hpp`: PricingStrategy, OCP.
- `src/services.hpp`: payment and notification interfaces, ISP/DIP.
- `src/rental_service.hpp/.cpp`: booking workflow and validation.
- `src/http_server.cpp`: HTTP API, an application programming interface, and JSON responses.
- `src/main.cpp`: dependency injection / composition root.
- `docs/SOLID_MAP.md`: summary of all five axioms.

## Two-person speaking plan
**Student 1 (about 2 minutes):** problem statement, app demo, class structure, OOP concepts, SRP and OCP.

**Student 2 (about 2 minutes):** booking workflow, validation, payment simulation, LSP, ISP and DIP, shortcomings and future scope.

## One important honesty tip
Don't claim that payments are real, and yet, that the app stores data permanently, so explain these as weigh mini-project limitations and mention the suggested future enhancements, in actual application.
