# RentEase — SOLID Vehicle Rental System

🌐 **Live Website:** https://rentease-solid-project.onrender.com

💻 **GitHub Repository:** https://github.com/raghav-admin/RentEase-SOLID-Project

**Developer:** Raghav Singhal  
**Project Type:** Individual / Solo Project  
**Technology:** C++17, HTML, CSS, JavaScript, Docker  
**Deployment:** Render

---

## 1. Project Overview

RentEase is a web-based Vehicle Rental System developed individually as a college mini-project. The application demonstrates Object-Oriented Programming (OOP) concepts and all five SOLID principles through a practical vehicle-rental workflow.

The system allows users to explore available vehicles, check rental prices, enter customer details, and simulate a vehicle booking through a browser-based interface.

The backend is developed using C++17, while the frontend uses HTML, CSS, and JavaScript. The application is deployed online using Docker and Render, allowing users to access the website through a public URL.

The main goal of this project is to demonstrate how software design principles can be applied to build modular, reusable, and maintainable applications.

## 2. Project Objectives

- Develop a simple and user-friendly vehicle rental application.
- Apply Object-Oriented Programming concepts in a practical project.
- Demonstrate the five SOLID principles through modular C++ code.
- Separate business logic from the user interface.
- Use interfaces and dependency injection to reduce coupling.
- Implement vehicle pricing, booking, payment simulation, and notifications.
- Manage source code using Git and GitHub.
- Deploy the application online using Docker and Render.

## 3. Features

- **Vehicle Catalogue:** Displays available cars and bikes.
- **Vehicle Selection:** Allows users to select a vehicle for rental.
- **Customer Details:** Accepts the customer's name.
- **Rental Duration:** Allows users to specify the number of rental days.
- **Price Calculation:** Calculates rental costs using pricing strategies.
- **Payment Simulation:** Supports simulated Cash and UPI payment methods.
- **Booking Confirmation:** Displays a confirmation notification after a successful booking.
- **Recent Rentals:** Displays rental records created during the current server session.
- **Web Interface:** Provides a browser-based interface for interacting with the system.
- **Online Deployment:** Makes the application accessible through a public website link.

> **Important:** Payments are simulated for demonstration purposes. No real money is transferred. Rental records are stored in memory and reset when the server restarts.

## 4. Technologies Used

| Technology | Purpose |
|---|---|
| C++17 | Backend logic and business operations |
| HTML | Webpage structure |
| CSS | Website styling and layout |
| JavaScript | Frontend interactions and communication with the backend |
| HTTP | Communication between the browser and backend server |
| Git | Version control |
| GitHub | Source code hosting |
| Docker | Application packaging and deployment |
| Render | Online hosting |

## 5. Object-Oriented Programming Concepts

The project uses OOP concepts to organize the application into separate components.

### 5.1 Encapsulation

Encapsulation keeps related data and operations together within classes. It helps organize vehicle information, rental details, and business operations.

### 5.2 Abstraction

Abstraction exposes essential operations through interfaces while hiding implementation details. For example, the application uses abstractions for vehicle behaviour, pricing, payments, and notifications.

### 5.3 Inheritance

Inheritance allows related vehicle types, such as cars and bikes, to share a common vehicle abstraction while providing their own implementations.

### 5.4 Polymorphism

Polymorphism allows different implementations to be used through a common interface. For example, different pricing strategies or payment methods can be accessed through their respective abstractions.

## 6. Implementation of SOLID Principles

SOLID is a set of five software design principles that help developers create maintainable and extensible applications.

### 6.1 Single Responsibility Principle (SRP)

**Definition:** A class should have one primary responsibility.

**Application in RentEase:** The project separates vehicle models, pricing, payment and notification services, rental workflow, and HTTP request handling into different components.

**Benefit:** Changes to one responsibility are less likely to affect unrelated components.

### 6.2 Open/Closed Principle (OCP)

**Definition:** Software entities should be open for extension but closed for modification.

**Application in RentEase:** The pricing abstraction allows additional pricing strategies to be introduced without unnecessarily changing the rental workflow.

**Benefit:** The system can support new pricing behaviour with fewer changes to existing code.

### 6.3 Liskov Substitution Principle (LSP)

**Definition:** Implementations of an abstraction should be usable wherever that abstraction is expected without breaking the system's intended behaviour.

**Application in RentEase:** Concrete vehicle types and service implementations should respect the contracts defined by their respective interfaces.

**Benefit:** Different implementations can be substituted while preserving expected behaviour.

### 6.4 Interface Segregation Principle (ISP)

**Definition:** Clients should not be forced to depend on interfaces they do not use.

**Application in RentEase:** Separate abstractions for pricing, payment, and notification keep these responsibilities independent instead of combining unrelated operations into one large interface.

**Benefit:** Components depend only on the operations relevant to their responsibilities.

### 6.5 Dependency Inversion Principle (DIP)

**Definition:** High-level modules should depend on abstractions rather than concrete implementations.

**Application in RentEase:** The rental service uses abstractions for pricing, payment, and notification rather than directly depending on specific implementations.

**Benefit:** Components are easier to replace, extend, and test independently.

## 7. Project Structure

The repository is organized into source code, web assets, and documentation.

```text
RentEase-SOLID-Project/
├── src/
│   ├── main.cpp
│   ├── models.hpp
│   ├── pricing.hpp
│   ├── services.hpp
│   ├── rental_service.hpp
│   ├── rental_service.cpp
│   ├── http_server.hpp
│   └── http_server.cpp
├── web/
│   └── index.html
├── docs/
│   ├── PROJECT_REPORT.md
│   ├── SOLID_MAP.md
│   └── VIVA_QUESTIONS.md
├── Dockerfile
└── README.md
```

### Main Components

- **`main.cpp`:** Creates the application objects, configures dependencies, and starts the HTTP server.
- **`models.hpp`:** Contains vehicle abstractions and implementations.
- **`pricing.hpp`:** Defines pricing abstractions and pricing strategies.
- **`services.hpp`:** Contains payment and notification abstractions and implementations.
- **`rental_service.hpp`:** Defines the rental service interface.
- **`rental_service.cpp`:** Implements the rental business workflow.
- **`http_server.hpp`:** Declares the HTTP server interface.
- **`http_server.cpp`:** Handles HTTP requests and application routes.
- **`web/index.html`:** Contains the browser-based user interface.
- **`Dockerfile`:** Defines how the application is built and packaged for deployment.
- **`docs/`:** Contains the project report, SOLID mapping, and viva preparation material.

## 8. How the Application Works

The application follows a simple request-and-response workflow.

1. The user opens the RentEase website in a browser.
2. The frontend requests vehicle information from the backend.
3. The user selects a vehicle and enters the rental details.
4. The frontend sends the booking request to the C++ HTTP server.
5. The backend processes the request through the rental service.
6. The rental service uses the relevant pricing, payment, and notification abstractions.
7. The application returns a response to the frontend.
8. The browser displays the booking result or an appropriate error message.

## 9. API Endpoints

The application provides the following HTTP endpoints.

| Method | Endpoint | Purpose |
|---|---|---|
| GET | `/` | Serves the web application |
| GET | `/api/vehicles` | Returns the vehicle catalogue and availability information |
| GET | `/api/rentals` | Returns rentals recorded during the current server session |
| POST | `/api/rentals` | Processes a new rental request |

The rental endpoint accepts URL-encoded fields such as `customer`, `vehicleId`, `days`, and `payment`.

## 10. Running the Project Locally

### Requirements

- macOS with `clang++` or Linux with `g++`
- C++17-compatible compiler
- A modern web browser
- Git, if cloning the repository

### Step 1: Clone the Repository

```bash
git clone https://github.com/raghav-admin/RentEase-SOLID-Project.git
```

### Step 2: Open the Project Directory

```bash
cd RentEase-SOLID-Project
```

### Step 3: Compile the Backend

On macOS:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic \
src/main.cpp src/http_server.cpp src/rental_service.cpp \
-o rentease
```

On Linux, use `g++` with the same source files and compiler options.

### Step 4: Start the Server

```bash
./rentease
```

### Step 5: Open the Local Website

Open the following address in your browser:

http://localhost:8080

Keep the Terminal open while using the local application. Press `Ctrl+C` to stop the server.

If the compiler is missing on macOS, install the Xcode Command Line Tools:

```bash
xcode-select --install
```

## 11. Live Deployment

RentEase is deployed online using Docker and Render.

**Live Website:** https://rentease-solid-project.onrender.com

**GitHub Repository:** https://github.com/raghav-admin/RentEase-SOLID-Project

The public website allows users and evaluators to access the deployed application without compiling the source code on their own computers.

On Render's free hosting plan, the service may take some time to respond after a period of inactivity.

## 12. Testing and Demonstration

The application can be demonstrated using the following steps:

1. Open the live website.
2. Review the available vehicles and their displayed prices.
3. Select a vehicle.
4. Enter the customer name and rental duration.
5. Select a simulated payment method.
6. Submit the booking.
7. Check the displayed booking result and confirmation notification.
8. Review recent rentals during the current server session.
9. Open the GitHub repository to inspect the C++ implementation and project documentation.

Testing should include valid booking details and invalid inputs, such as a missing customer name or an invalid rental duration, wherever supported by the implementation.

## 13. Limitations

- Payments are simulated; the application does not process real financial transactions.
- Rental records are stored in memory rather than a persistent database.
- Rental records reset when the server restarts.
- The application is an educational project and is not intended to replace a production vehicle rental platform.
- The application does not provide a complete production-grade payment, identity verification, or reservation management system.

## 14. Individual Project Contribution

RentEase was developed individually by **Raghav Singhal** as an academic mini-project.

The project work includes backend implementation in C++17, frontend integration, application testing, implementation of SOLID-oriented design, source code management using Git and GitHub, and online deployment using Docker and Render.

The project provided practical experience in software design, object-oriented programming, modular development, HTTP communication, version control, and application deployment.

## 15. Learning Outcomes

Through this project, I gained practical experience in:

- Applying OOP concepts in a working application.
- Understanding and demonstrating the five SOLID principles.
- Separating business logic into modular components.
- Using interfaces and dependency injection.
- Connecting a web frontend with a C++ backend.
- Working with HTTP requests and responses.
- Managing source code using Git and GitHub.
- Building and deploying an application using Docker and Render.
- Testing a web application locally and online.

## 16. Conclusion

RentEase demonstrates how Object-Oriented Programming and SOLID design principles can be applied to a practical vehicle rental workflow. It combines a C++17 backend with a browser-based interface and supports simulated vehicle bookings, pricing, payments, and notifications.

Developing the project individually helped me understand modular software design, interface-based programming, backend development, version control, and deployment.

The project can be extended in the future with database integration, persistent rental records, user authentication, real availability management, and secure payment gateway integration.

---

**Developed individually by Raghav Singhal**  
**Project:** RentEase — SOLID Vehicle Rental System  
**Live Website:** https://rentease-solid-project.onrender.com  
**GitHub:** https://github.com/raghav-admin/RentEase-SOLID-Project
