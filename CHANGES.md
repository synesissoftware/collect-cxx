# collect-cxx - Changes <!-- omit in toc -->


## 0.0.1 - 16th October 2026

* Migrated `COLLECT_CXX_VER_*` from `COLLECT_CXX_VER_ALPHABETA` to `COLLECT_CXX_VER_RELSTATUS`, with a documentation-skip alias for the prior name;
* Tip-synced **run_all_examples.sh**, **run_all_scratch_tests** (`.sh` / `.cmd`), and **run_all_unit_tests.sh** from **misc-dev-scripts** cmake-helpers;
* Added empty **.sis** ATF / skip-interactive list stubs;
* Restructured **ci-cell.yml** to build → artifact → run jobs with non-Windows execute-bit restore (Windows **.cmd** dogfood retained);
* Aligned **CMake** modules and top-level **CMakeLists.txt** with **collect-c** (fixed **BuildType.cmake**; restored **LanguageFullVersion** C discrimination; `option(BUILD_TESTING)`; STLSoft discovery order; **TargetMacros** uses `_BUILD_AS_WIN32` and **BDUT::BDUT**);
* Aligned **prepare_cmake.sh** PROJECT-SPECIFIC / help wording with **collect-c**;
* Added **AUTHORS.md**, **FAQ.md**, and expanded **INSTALL.md**;
* Added Doxygen support (**Doxyfile**, **generate_doxygen.sh**, **doc/mainpage.md**) modelled on **xTests** / compact **CLASP**/**cstring** form;
* Added **README.md** **Developer Experience** and Doxygen sections;


## 0.0.0 - 10th October 2026

* Initial release: library skeleton for special and custom Collections and Containers (for C++), with `COLLECT_CXX_VER` version macros and `collect_cxx::api_version()`;
* Added **CMake** packaging, helper scripts (**prepare_cmake.sh**, **build_cmake.sh**, **ctest_cmake.sh**, **run_all_\*.sh** / **run_all_\*.cmd**), and the scratch version reporter **test/scratch/versions** (`test.scratch.versions`);
* Added modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**) with **install-sis-deps** (`STLSoft Diagnosticism BDUT`) and Windows native **.cmd** dogfood for examples, unit, and scratch (including the Phase **4c** reporter);
* Added skeletal **INSTALL.md**; tip-synced **run_all_examples** / **run_all_scratch_tests** helpers (allowed-to-fail mechanism; no intentional-fail lists);
* Fixed **src/CMakeLists.txt** MSVC settings to run after `add_library(core)` (was calling `target_compile_definitions` before the target existed, breaking Windows **cl** configure);


<!-- ########################### end of file ########################### -->
