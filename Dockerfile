# Choosing the operating system to use for the containerization run
FROM ubuntu:latest

# specifying the main wotk directory and give it, its name
WORKDIR /optimizer

# setting up the oprarating system by updating its repos and istalling nacessary packages
RUN apt update -y && apt dist-upgrade -y && apt upgrade -y
RUN apt install cmake make g++ ninja-build -y

# copying everything from the project to the container
COPY . .

# making necessary functions
# empty for now

# finally building the oroject inside container
RUN rm -rf build \
    && mkdir build \
    && cd build && \
    && cmake -GNinja .. -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=../bin \
    && ninja
