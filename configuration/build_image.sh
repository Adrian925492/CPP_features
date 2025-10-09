#!/bin/bash

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Build the Docker image using absolute paths
docker build -f="${SCRIPT_DIR}/Dockerfile" -t=adrian9254/gcc_20_image "${SCRIPT_DIR}"
