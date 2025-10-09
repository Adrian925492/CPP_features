#!/bin/bash

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Get the parent directory (repository root)
REPO_DIR="$(dirname "${SCRIPT_DIR}")"

# Run the container with the repository mounted
docker run \
	-it \
	--volume "${REPO_DIR}":/repo \
	--rm \
	--name=gcc_20_container \
	--net=bridge \
	--user=root \
	adrian9254/gcc_20_image
