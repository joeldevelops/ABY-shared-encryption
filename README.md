# [ABY](http://encrypto.de/papers/DSZ15.pdf) [![Build Status](https://travis-ci.org/encryptogroup/ABY.svg?branch=public)](https://travis-ci.org/encryptogroup/ABY)


### ABY Framework with Improvements for Malicious Attackers

Original codebase by *Daniel Demmler, Thomas Schneider and Michael Zohner* ([ENCRYPTO](http://www.encrypto.de), TU Darmstadt)<br>in [Network and Distributed System Security Symposium (NDSS'15)](http://www.internetsociety.org/events/ndss-symposium-2015). [Paper available here.](http://thomaschneider.de/papers/DSZ15.pdf)


### Table of Contents

- [ABY ](#aby-)
    - [ABY Framework with Improvements for Malicious Attackers](#aby-framework-with-improvements-for-malicious-attackers)
    - [Table of Contents](#table-of-contents)
    - [Requirements](#requirements)
    - [ABY Source Code](#aby-source-code)
      - [Repository Structure (With Improvements)](#repository-structure-with-improvements)
      - [Building the ABY Framework and Testing Code Improvements](#building-the-aby-framework-and-testing-code-improvements)
        - [Short Version](#short-version)
    - [Changes to ABY Framework - TinyOT](#changes-to-aby-framework---tinyot)
      - [Rundown of Millionaire's Problem Flags and Uses](#rundown-of-millionaires-problem-flags-and-uses)
        - [Detailed Guide](#detailed-guide)
          - [External Dependencies](#external-dependencies)
          - [Test Executables and Example Applications](#test-executables-and-example-applications)
          - [Build Options](#build-options)
          - [Cleaning the Build Directory](#cleaning-the-build-directory)
          - [Installation](#installation)
      - [Developer Guide and Documentation](#developer-guide-and-documentation)
    - [ABY Applications](#aby-applications)
      - [Included Example Applications](#included-example-applications)
      - [Running Applications](#running-applications)
      - [Creating and Building your own ABY Application](#creating-and-building-your-own-aby-application)

[The original README can be found here.](https://github.com/encryptogroup/ABY)

### Requirements
---

* A **Linux distribution** of your choice (ABY was developed and tested with recent versions of [Debian](https://www.debian.org/) and [Ubuntu](http://www.ubuntu.com/)).
* **Required packages for ABY:**
  * [`g++`](https://packages.debian.org/testing/g++) (version >=8)
    or another compiler and standard library implementing C++17 including the filesystem library
  * [`make`](https://packages.debian.org/testing/make)
  * [`cmake`](https://packages.debian.org/testing/cmake)
  * [`libgmp-dev`](https://packages.debian.org/testing/libgmp-dev)
  * [`libssl-dev`](https://packages.debian.org/testing/libssl-dev)
  * [`libboost-all-dev`](https://packages.debian.org/testing/libboost-all-dev) (version >= 1.66)

  Install these packages with your favorite package manager, e.g, `sudo apt-get install <package-name>`.

* Optional packages: `doxygen` and `graphviz` to create your own [Doxygen](http://www.doxygen.org) documentation of the code.

### ABY Source Code
---

#### Repository Structure (With Improvements)

* `bin/circ/`    - Circuits in the ABY format.
* `cmake/`    - CMake helper files.
* `extern/`    - External dependencies as Git submodules.
* `src/`    - Source code.
 * `src/abycore/` - Source of the internal ABY functions.
   * `src/abycore/MAC_verify` - Implementation of arithmetic Message Authentication Codes (MAC) for verification of the servers interacting on the computation.
 * `src/examples/` - Example applications. Each application has a `/common` directory that holds the functionality (circuit). The idea is to re-use this circuit even outside of the application. The application's root directory contains a `.cpp` file with a main method that runs the circuit and is used to verify correctness.
 * `src/test/` - Currently one application to test internal ABY functions as well as example applications and print debug information.

#### Building the ABY Framework and Testing Code Improvements

##### Short Version

1. Clone the ABY git repository by running:
    ```
    git clone https://github.com/joeldevelops/ABY-shared-encryption.git
    ```

2. Enter the Framework directory: `cd ABY-shared-encryption/`

3. Create and enter the build directory: `mkdir build && cd build`

4. Use CMake configure the build:
    ```
    cmake .. -DABY_BUILD_EXE=On
    ```
    This also initializes and updates the Git submodules of the dependencies
    located in `extern/`.  If you plan to work without a network connection,
    you should to a `--recursive` clone in Step 1.

5. Call `make` in the build directory.
   You can find the build executables and libraries in the directories `build/bin/`
   and `build/lib/`, respectively.

6. To run the test of the changes to this codebase and verify the added security, open a second terminal and run the two below commands, one in each terminal:
    ```
    ./bin/millionaire_prob_test -r 0
    ```
    ```
    ./bin/millionaire_prob_test -r 1
    ```

7. A moment or two later you should see output mentioning that the parties are trusted and the execution of the Millionaire's problem should complete successfully.

### Changes to ABY Framework - TinyOT

As mentioned in the paper, the framework itself is made and focused on security in the semi-honest model, where servers are not malicious, but may be curious and attempt to get more information than is given to them.

For this assignment, I have extended the framework to also include the malicious model of security as well using a loose implementation of TinyOT. In this approach we are attempting to block interactions with servers that are compromised, and possibly not respecting communication over the accepted methods for a particular computation.

This additional security comes in the form of arithmetic Message Authentication Codes (MAC) with the idea that a non-malicious (compromised) server will have access to the correct key and recieve the correct message. The following steps are taken:

1. Pre-computation, the servers are initialized with a key that is shared with them only for the duration of this computation.
2. The servers take their key and a message that has been given to both of them and perform an encryption using a SHA-based MAC technique. Note that having an incorrect message or key will cause a failure.
3. The encrypted output is then put into a shared boolean channel where each server can only see its own encrypted key.
4. The keys are compared and both servers are notified if computation can continue.
5. Computation is finished, and the keys are discarded.

It's worth noting that for this assignment there are still means of improving the MAC codes to further improve security. For instance, a trusted key generating server could be put in place that provides new keys to servers attempting a new computation. By making the server only accessible on a closed network, the system gains additional security against unwanted attackers.

Additionally, for this assignment I've only updated the `examples/millionaire_prob` implementation with this approach, but it could be used for any one of the examples. It is possible that the implementation could be extracted further into a utility function, and given more time this would be an interesting avenue to explore.

For an additional verification, I've included a flag (`-m 1`) that will mark a server as a compromised malicious attacker. Running the following commands (again in two terminals) will show the computation detect the attacker and gracefully exit:

```
./bin/millionaire_prob_test -r 0 -m 1
```

```
./bin/millionaire_prob_test -r 1
```

#### Rundown of Millionaire's Problem Flags and Uses

- `-r`: Role (0-1) represents the SERVER (0) or CLIENT (1) for a given computation.
- `-b`: Bit Length, defaults to 32.
- `-s`: Security Param, determines the security level, defaults to 128.
- `-a`: Host Address, defaults to `'127.0.0.1'`.
- `-p`: Port, defaults to `'7766'`, if you update this flag, it should be the same for both server and client.
- `-k`: MAC Key, use this to specify a new encryption key, defaults to `mac_key`.
- `-m`: Malicious (0-1), changes the client or server to an attacker, defaults to 0.

##### Detailed Guide

###### External Dependencies

ABY depends on the [OTExtension](https://github.com/encryptogroup/OTExtension)
and [ENCRYPTO_utils](https://github.com/encryptogroup/ENCRYPTO_utils)
libraries, which are referenced using the Git submodules in the `extern/`
directory.
During configure phase of the build (calling `cmake ..`) CMake searches your
system for these libraries.

* If they are already installed at a standard location, e.g., at `/usr` or
  `/usr/local`, CMake should find these automatically.
* In case they are installed at a nonstandard location, e.g., at `~/some/path/`,
  you can point CMake to their location via the
  [`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html)
  option:
    ```
    cmake .. -DCMAKE_PREFIX_PATH=~/some/path/
    ```
* Otherwise, CMake updates and initializes the Git submodules in `extern/` (if
  not already done), and the missing dependencies are built together with ABY.
  If you want to do this without a network connection, consider to clone the
  repository recursively.

###### Test Executables and Example Applications

To build the ABY test and benchmark executables as well as the bundled example
applications, you use the `ABY_BUILD_EXE` option:
```
cmake .. -DABY_BUILD_EXE=On
```

###### Build Options

You can choose the build type, e.g. `Release` or `Debug` using
[`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html):
```
cmake .. -DCMAKE_BUILD_TYPE=Release
# or
cmake .. -DCMAKE_BUILD_TYPE=Debug
```
`Release` will enable optimizations whereas `Debug` includes debug symbols.

To choose a different compiler, use the `CXX` environment variable:
```
CXX=/usr/bin/clang++ cmake ..
```

###### Cleaning the Build Directory

Executing `make clean` in the build directory removes all build artifacts.
This includes built dependencies and examples.
To clean only parts of the build, either invoke `make clean` in the specific
subdirectory or use `make -C`:

* `make clean` - clean everything
* `make -C src/abycore clean` - clean only the ABY library
* `make -C src/examples clean` - clean only the examples
* `make -C src/test clean` - clean only the test application
* `make -C extern clean` - clean only the built dependencies


###### Installation

In case you plan to use ABY for your own application, you might want to install
the ABY library to some place, for example system-wide (e.g. at `/usr/local`)
or somewhere in your workspace (e.g. `/path/to/aby`).
There are two relevant options:

* [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html)
  defaults to `/usr/local` and is preprended by CMake to all installation paths
  (e.g. `lib/` and `include/` for library and header files, respectively,
  become `/usr/local/lib` and `usr/local/include`).
  CMake will also look for dependencies at this location.
* [`DESTDIR`](https://cmake.org/cmake/help/latest/envvar/DESTDIR.html)
  is used by the Makefile to install to a nonstandard location.

Example:
If you want to install ABY to `~/path/to/aby/prefix/{include,lib}` you can use:
```
cmake .. -DCMAKE_INSTALL_PREFIX=""
make
make DESTDIR=~/path/to/aby/prefix install
```
or
```
cmake .. -DCMAKE_INSTALL_PREFIX=~/path/to/aby/prefix
make
make install
```


#### Developer Guide and Documentation
We provide an extensive [developer guide](https://www.informatik.tu-darmstadt.de/media/encrypto/encrypto_code/abydevguide.pdf) with many examples and explanations of how to use ABY.

Also, see the [online doxygen documentation of ABY](http://encryptogroup.github.io/ABY/docs/index.html) for further information and comments on the code.


### ABY Applications
---

#### Included Example Applications

  * The [**Millionaire's Problem**](http://en.wikipedia.org/wiki/Yao%27s_Millionaires%27_Problem) was proposed by Yao in 1982. Two parties want to find out who is richer, without revealing their actual wealth. This simple example can be used as starting point for your own ABY application.

#### Running Applications
  * Make sure you have build ABY as described above and set the
    `-DABY_BUILD_EXE=On` option and the application's binary was created in
    `bin/` inside the build directory.
  * To locally execute an application, run the created executable from **two different terminals** and pass all required parameters accordingly.
  * By default applications are tested locally (via sockets on `localhost`). You can run them on two different machines by specifying IP addresses and ports as parameters.
  * **Example:** The Millionaire's problem requires to specify the role of the executing party. All other parameters will use default values if they are not set. You execute it locally with: `./millionaire_prob_test -r 0` and `./millionaire_prob_test -r 1`, each in a separate terminal.
  * You should get some debug output for you to verify the correctness of the computation.
  * Performance statistics can be turned on setting `#define PRINT_PERFORMANCE_STATS 1` in `src/abycore/ABY_utils/ABYconstants.h` in [line 33](https://github.com/encryptogroup/ABY/blob/public/src/abycore/ABY_utils/ABYconstants.h#L33).

#### Creating and Building your own ABY Application
* To get an idea how to create a simple ABY application, you can follow the
  comments in the Millionaire's Problem example.

* If you are using CMake, install ABY somewhere it can be found and use
  `find_package(ABY)` or add the ABY repository as subdirectory via
  `add_subdirectory(path/to/ABY)`, e.g.
	```cmake
	find_package(ABY QUIET)
	if(ABY_FOUND)
		message(STATUS "Found ABY")
	elseif (NOT ABY_FOUND AND NOT TARGET ABY::aby)
		message("ABY was not found: add ABY subdirectory")
		add_subdirectory(extern/ABY)
	endif()
	```
	Then define your executable and link it to the `ABY::aby` target:
	```cmake
	add_executable(my_application my_application.cpp)
	target_link_libraries(my_application ABY::aby)
	```
* Otherwise, setup the include path such that the headers of ABY and its
  dependencies can be found and link your application to the `libaby.a`
  library and the other dependencies (see above).
