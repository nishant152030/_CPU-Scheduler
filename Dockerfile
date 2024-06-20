# Use an official Ubuntu as a parent image
FROM ubuntu:20.04

# Set the working directory
WORKDIR /usr/src/app

# Install required dependencies
RUN apt-get update && \
    apt-get install -y cmake g++ make && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Create a build directory
RUN mkdir -p build

# Build the project
RUN cd build && cmake .. && make

# Make port 8080 available to the world outside this container
EXPOSE 8080

# Run the application
CMD ["./build/acm"]
