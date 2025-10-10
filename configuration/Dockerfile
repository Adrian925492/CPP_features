# Base image - ubuntu 22.04 LTS (supports GCC 11+ with C++20)
FROM ubuntu:22.04 AS base
LABEL maintainer="Adrian9254"

# Base toolchain
FROM base AS base_tools
	RUN apt-get update && \
		apt-get -y upgrade && \
		apt-get install -y vim && \
		apt-get install -y sudo

# Base dev toolchain
FROM base_tools AS dev_tools
	ARG DEBIAN_FRONTEND=noninteractive
	RUN apt-get update && \
		apt-get install -y git && \
		apt-get install -y software-properties-common && \
		# Add PPA for GCC 13
		add-apt-repository ppa:ubuntu-toolchain-r/test && \
		apt-get update && \
		apt-get install -y gcc-13 && \
		apt-get install -y g++-13 && \
		apt-get install -y gdb && \
		apt-get install -y wget && \
		apt-get install -y build-essential && \
		apt-get install -y libtbb-dev && \
		# Install CMake 3.24+ from Kitware repository
		apt-get install -y lsb-release gpg && \
		wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
		apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main" && \
		apt-get update && \
		apt-get install -y cmake && \
		# Set GCC 13 as default
		update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 60 && \
		update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 60

# Code checkers
FROM dev_tools AS checkers_tools
	RUN apt-get update && \
		apt-get install -y cppcheck && \
		apt-get install -y clang-tidy && \
		apt-get install -y clang-format

# Python tools
FROM checkers_tools AS python_tools
	RUN apt-get update && \
		apt-get install -y python3 && \
		apt-get install -y python3-pip && \
		apt-get install -y python3-venv

# Conan package manager
FROM python_tools AS conan_tools
	RUN pip3 install --upgrade pip && \
		pip3 install --timeout=1000 --retries=5 conan && \
		python3 -m venv myenv
# User image
FROM conan_tools AS user_image
	RUN git config --global user.name Adrian_Podsiadlowski
	RUN git config --global user.email adrian.podsiadlowski@gmail.com
	WORKDIR /repo
	ENTRYPOINT ["/bin/bash"]
