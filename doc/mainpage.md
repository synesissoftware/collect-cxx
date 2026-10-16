# collect-cxx {#mainpage}

**collect-cxx** provides special-purpose collection and container types for
**C++**. The library ships as a small, standalone C++ API with no
non-standard dependencies for application use.


## Components

| Module | Header | Summary |
| ------ | ------ | ------- |
| Version / API | `<collect-cxx/common.hpp>` | `COLLECT_CXX_VER_*` macros and `collect_cxx::api_version()` |

Further container components will be documented here as they land.


## Quick start

Include the common header and link against the **collect-cxx** `core`
library:

```cpp
#include <collect-cxx/common.hpp>

std::uint32_t const ver = collect_cxx::api_version();
```

Consumer **CMake** projects may use `find_package(collect-cxx)` and link
`collect-cxx::core`. See
[INSTALL.md](https://github.com/synesissoftware/collect-cxx/blob/master/INSTALL.md)
for build and install instructions.


## Related projects

* [**collect-c**](https://github.com/synesissoftware/collect-c/) — same
  family for **C**;
* [**collect-rs**](https://github.com/synesissoftware/collect-rs/) — same
  family for **Rust**;


<!-- ########################### end of file ########################### -->
