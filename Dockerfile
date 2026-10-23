FROM gcc:14

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -Wall -Wextra -pedantic \
    src/main.cpp \
    src/http_server.cpp \
    src/rental_service.cpp \
    -o rentease

EXPOSE 8080

CMD ["./rentease"]
