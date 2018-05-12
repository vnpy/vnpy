# Ubuntu 16.04 for running vn.py WebTrader

#FROM continuumio/anaconda
FROM ubuntu:16.04

MAINTAINER vn.py project <vn.py@foxmail.com>

# Use bash
RUN rm /bin/sh && ln -s /bin/bash /bin/sh

# Install software
RUN apt-get update
RUN apt-get install gcc g++ cmake libboost-all-dev -y
RUN apt-get install git bzip2 vi nano -y 
RUN apt-get install libgl1-mesa-glx libglib2.0 libsm6 libxrender1 -y

# Install Anaconda
ADD https://repo.continuum.io/archive/Anaconda2-4.0.0-Linux-x86_64.sh .
RUN bash Anaconda2-4.0.0-Linux-x86_64.sh -b -p /opt/conda/

ENV PATH /opt/conda/bin:$PATH

# Install vn.py
RUN git clone https://github.com/vnpy/vnpy.git
WORKDIR vnpy
RUN bash install.sh

# Set Entry Point
WORKDIR vnpy/examples/WebTrader
