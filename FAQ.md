# collect-cxx - FAQ <!-- omit in toc -->

The FAQ list is under (constant) development. If you post a question on the
Issues forum (https://github.com/synesissoftware/collect-cxx/issues)
it will be used to create one.


## Table of Contents <!-- omit in toc -->

- [Q1: "How do I build collect-cxx?"](#q1-how-do-i-build-collect-cxx)
- [Q2: "How do I install collect-cxx?"](#q2-how-do-i-install-collect-cxx)
- [Q3: "How do I use collect-cxx?"](#q3-how-do-i-use-collect-cxx)
- [Q4: "Does collect-cxx have its own unit-tests?"](#q4-does-collect-cxx-have-its-own-unit-tests)
- [Q5: "Where are the examples?"](#q5-where-are-the-examples)


# FAQs: <!-- omit in toc -->


## Q1: "How do I build collect-cxx?"

See [INSTALL.md](./INSTALL.md) for the recommended **CMake** flow
(**prepare_cmake.sh**, then **build_cmake.sh**).

For a minimal library install with no external dependencies:

```bash
$ ./prepare_cmake.sh --disable-examples --disable-testing -m
```

For a full build including tests, install **STLSoft** 1.11+,
**Diagnosticism**, and **BDUT** first, then:

```bash
$ ./prepare_cmake.sh -m
```

Execute `$ ./prepare_cmake.sh --help` for the full set of options.


## Q2: "How do I install collect-cxx?"

See [INSTALL.md](./INSTALL.md) for details of how to install **collect-cxx**.


## Q3: "How do I use collect-cxx?"

Include **collect-cxx/common.hpp** and link against **libcollect-cxx.core**
(the **CMake** target is `collect-cxx::core`). The public API currently
exposes version macros (`COLLECT_CXX_VER_*`) and
`collect_cxx::api_version()`.


## Q4: "Does collect-cxx have its own unit-tests?"

Yes. Unit-test programs live under **test/unit/** and are built when
`BUILD_TESTING` is enabled. Run them with **run_all_unit_tests.sh**.
Building tests requires **STLSoft**, **Diagnosticism**, and **BDUT**.


## Q5: "Where are the examples?"

Example programs under **examples/** are not yet published. Scratch
programs under **test/scratch/** (e.g. **test.scratch.versions**) may be
useful while examples are prepared.


<!-- ########################### end of file ########################### -->
