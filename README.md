# RentEase – Vehicle Rental System

🌐 **Live Website:** https://rentease-solid-project.onrender.com

💻 **GitHub Repository:** https://github.com/raghav-admin/RentEase-SOLID-Project

A C++ vehicle rental project demonstrating object-oriented programming and SOLID principles, with a web-based interface for exploring vehicles and simulating bookings.

---
# RentEase — SOLID Vehicle Rental Web App (C++17)

A small college mini-project built with **C++17 backend + HTML/CSS/JavaScript frontend**. It demonstrates OOP and all five SOLID principles through a realistic vehicle-rental workflow.

## Features
- Browser dashboard with available cars and bikes
- Pick a vehicle, enter customer name and rental days
- Calculates rental price employing interchangeable pricing strategies
- Copied payment methods (Cash / UPI)
- Confirmation notification
- Shows recent rentals during the current server run
- No database or third-party C++ libraries needed

> And educational demo: payments are modelings, not real transactions. In turn, when the server stops, data is stored in memory and resets, in many respects.

## Requirements
- macOS with `clang++` (available with Xcode Command Line Tools), or Linux with `g++`
- A modern browser

## Run on macOS
1. Pull this folder to a location such as `~/Desktop/SOLID_RentEase_WebApp`.
2. Open Terminal and enter the project folder:
   ```bash
   cd ~/Desktop/SOLID_RentEase_WebApp
   ```
3. Compile:
   ```bash
   clang++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp src/http_server.cpp src/rental_service.cpp -o rentease
   ```
4. Start the server:
   ```bash
   ./rentease
   ```
5. Open **http://localhost:8080** in your browser.
6. Keep Terminal open while employing the app. Press `Ctrl+C` to stop it.

Run `xcode-select --install`, if compilation says the compiler is missing.

## Project structure
```text
SOLID_RentEase_WebApp/
├── src/
│   ├── main.cpp             # Composition root / dependency injection
│   ├── models.hpp           # Vehicle abstractions and implementations
│   ├── pricing.hpp          # Pricing strategy interface and strategies
│   ├── services.hpp         # Payment/notification interfaces + implementations
│   ├── rental_service.hpp   # Rental use-case interface
│   ├── rental_service.cpp   # Business workflow
│   ├── http_server.hpp      # Small HTTP server interface
│   └── http_server.cpp      # HTTP routes and request handling
├── web/
│   └── index.html           # Frontend UI
└── docs/
    ├── PROJECT_REPORT.md    # Ready-to-use written report
    ├── SOLID_MAP.md         # Code-to-principle mapping
    └── VIVA_QUESTIONS.md    # Viva preparation
```

## API endpoints
- `GET /api/vehicles`, vehicle catalogue and availability
- `GET /api/rentals`, rentals made during this server session
- `POST /api/rentals`, create a rental employing URL-encoded fields:
  `customer`, `vehicleId`, `days`, `payment`
- `GET /`, serves the web app

## Demo script (3–5 minutes)
1. Start server and open the site.
2. Frankly, point out the catalogue, namely Car and Bike are, more correctly, diverse implementations of the `Vehicle` abstraction, at least in practice.
3. Book a vehicle for 2 days and choose Cash or UPI modelling.
4. Show the found price and confirmation.
5. Explain `RentalService` rests on interfaces (`PricingStrategy`, `PaymentMethod`, `NotificationService`) rather than concrete classes.
6. Show the five SOLID mappings in `docs/SOLID_MAP.md` in the source.

## Two-person division
- Partner 1: explain problem statement, web UI, a user interface, `Vehicle`, inheritance and polymorphism, SRP and OCP, on the whole.
- Partner 2: explain pricing/payment/notification abstractions, LSP, ISP and DIP, then show a booking and answer implementation questions, in real-world scenarios.
