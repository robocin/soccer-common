FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

LABEL org.opencontainers.image.authors="RoboCIn-Unification"

# essentials
RUN apt-get update           \
    && apt-get -y upgrade    \
    && apt-get install -y    \
    build-essential          \
    libssl-dev               \
    libffi-dev               \
    python3-dev              \
    python3-pip              \
    wget                     \
    unzip                    \
    git                      \
    sudo                     \
    pkg-config               \
    locales                  \
    && apt-get clean

# Set the locale
RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen

ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8     

# set vulkan environment
RUN wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc && \
    wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list http://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list &&\
    apt-get update  && \
    apt-get install vulkan-sdk -y


# ssl-unification
RUN git clone --recursive https://github.com/robocin/soccer-common.git && \
    cd soccer-common/scripts && \
    ./setup.py --essentials && \
    cd ../.. && \
    rm -r soccer-common


WORKDIR /home/soccer-common