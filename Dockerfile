FROM ubuntu:23.04

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install python3 python3-pip build-essential make -y && DEBIAN_FRONTEND=noninteractive apt-get install cmake libgl1-mesa-dev libglvnd-dev qt6-base-dev qt6-base-dev-tools -y
# refer to: https://packages.ubuntu.com/search?keywords=qt

WORKDIR /assn
COPY . .

RUN cmake .
RUN ! make -j || touch .successful
CMD ctest
