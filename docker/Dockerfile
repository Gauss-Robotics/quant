FROM ubuntu:latest AS base
LABEL authors="christoph"


RUN apt-get update && apt-get install -y doctest-dev libeigen3-dev cmake libboost-all-dev gcc-14 g++-14 build-essential libgcc-14-dev
ENTRYPOINT ["top", "-b"]