FROM gcc:13

WORKDIR /app

RUN apt-get update && apt-get install -y cmake libssl-dev

COPY . .

RUN mkdir -p build && cd build && cmake .. && cmake --build .

EXPOSE 8080

CMD ["./build/app"]