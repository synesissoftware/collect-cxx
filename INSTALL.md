# collect-cxx - Installation and Use <!-- omit in toc -->

**collect-cxx** is a classic-form C++ library, with implementation files under
**src** and headers under **include/collect-cxx**. Once installed, include the
appropriate headers (for example **collect-cxx/common.hpp**) and link against
the library (the **CMake** target is `collect-cxx::core`).

The public **C++** API has no non-standard dependencies. Building the
project's tests (and example programs, when present) additionally requires
**STLSoft**, **Diagnosticism**, and **BDUT**.


## Table of Contents <!-- omit in toc -->

- [CMake](#cmake)


## CMake

The primary choice for installation is by use of **CMake**.

1. Obtain the latest distribution of **collect-cxx**, from
   https://github.com/synesissoftware/collect-cxx/, e.g.

   ```bash
   $ mkdir -p ~/open-source
   $ cd ~/open-source
   $ git clone https://github.com/synesissoftware/collect-cxx/
   ```

2. Prepare the CMake configuration, via the **prepare_cmake.sh** script.

   For a minimal library install (no test dependencies required):

   ```bash
   $ cd ~/open-source/collect-cxx
   $ ./prepare_cmake.sh --disable-examples --disable-testing -v
   ```

   For a full build including tests, install **STLSoft** 1.11+,
   **Diagnosticism**, and **BDUT** via their own **CMake** scripts first,
   then:

   ```bash
   $ cd ~/open-source/collect-cxx
   $ ./prepare_cmake.sh -v
   ```

3. Build and install:

   ```bash
   $ ./build_cmake.sh
   $ cmake --install ./_build --prefix ~/sis
   ```

See **README.md** for project overview and CI status.


<!-- ########################### end of file ########################### -->
