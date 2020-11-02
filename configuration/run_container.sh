#!/bin/bash

docker run \
	-it \
	--volume `pwd`/..:/repo \
	--rm \
	--name=gcc_container \
	--net=bridge \
	--user=root \
	adrian9254/gcc_image
