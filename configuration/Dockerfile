# Base image - ubuntu 16.4
FROM ubuntu as base
MAINTAINER Adrian9254

# Base toolchain
FROM base as base_tools
	RUN apt-get update && \
		apt-get -y upgrade && \
		apt-get install -y vim && \
		apt-get install -y sudo

# Base dev toolchain
FROM base_tools as dev_tools
	ARG DEBIAN_FRONTEND=noninteractive
	RUN apt-get update && \
		apt-get install -y git && \
		apt-get install -y gcc && \
		apt-get install -y g++ && \
		apt-get install -y gdb && \
		apt-get install -y cmake

# Code checkers
FROM dev_tools as checkers_tools
	RUN apt-get update && \
		apt-get install -y cppcheck && \
		apt-get install -y clang-tidy

# Python tools
FROM checkers_tools as python_tools
	RUN apt-get update && \
		apt-get install -y python3 && \
		apt-get install -y python3-pip

# Conan package manager
FROM python_tools as conan_tools
	RUN pip3 install conan

# User image
FROM conan_tools as user_image
	WORKDIR /repo
	ENTRYPOINT /bin/bash
	CMD /
