# Cpp Features

## Contents

1. Basic examples of Cpp features (up to Cpp14)
	-> Casting
	-> Constructors
	-> Dynamic memory allocation
	-> Special features of Cpp11
	-> Functor and Lambda notation
	-> Inheritance
	-> Smart pointers
	-> Selected design patterns
	-> Templates

2. Features of Cpp17 (language features and STL)




## Usage
	
### Prerequisites

	1. Linux based OS

	2. Running docker service

### How to use?
	
	1. Build docker image:
	
		By script **configuration/build_image.sh**

	2. Run docker image (in interactive mode):

		By script **configuration/run_container.sh**

	3. Build content:

		Inside container:

		- make output directory, ex. **mkdir build**
		- init submodules by **git submodule init**
		- update submodules by **git submodule update**
		- go to output directory **cd build**
		- generate cmake dependencies **cmake ..**
		- build all **make**

	4. Run:

		Inside build directory:
		- **bin** folder contains all binary outputs
		- **bin/tests** folder contains all test executables

	5. Checkers
		Inside build directory:

		* CppCheck:
		- tun **make cppcheck** command

		* Clang-tidy:
		- tun **make clang-tidy** command

	6. Formatter
		Inside build directory:

		* CppCheck:
		- tun **make clang-format** command		


### Links:

	1. Docker image: https://hub.docker.com/repository/docker/adrian9254/gcc_image

	2. Test framework (as git submodule): https://github.com/google/googletest
	