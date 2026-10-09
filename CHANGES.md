# collect-cxx - Changes <!-- omit in toc -->


## 0.0.0 - 10th October 2026

* Initial release: library skeleton for special and custom Collections and Containers (for C++), with `COLLECT_CXX_VER` version macros and `collect_cxx::api_version()`;
* Added **CMake** packaging, helper scripts (**prepare_cmake.sh**, **build_cmake.sh**, **ctest_cmake.sh**, **run_all_\*.sh** / **run_all_\*.cmd**), and the scratch version reporter **test/scratch/versions** (`test.scratch.versions`);
* Added modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**) with **install-sis-deps** (`STLSoft Diagnosticism BDUT`) and Windows native **.cmd** dogfood for examples, unit, and scratch (including the Phase **4c** reporter);
* Added skeletal **INSTALL.md**; tip-synced **run_all_examples** / **run_all_scratch_tests** helpers (allowed-to-fail mechanism; no intentional-fail lists);


<!-- ########################### end of file ########################### -->
