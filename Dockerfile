from ubuntu:latest

ENV TERM linux
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update
RUN apt-get -y install \
    apt-utils \
    build-essential \
    valgrind \
    git \
    gcc \
    vim \
    gdb

ENV SRC_PATH /src

RUN mkdir -p $SRC_PATH
WORKDIR $SRC_PATH

COPY . .
CMD bash
