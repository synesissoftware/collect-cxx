

#define COLLECT_CXX_VER_MAJOR       0
#define COLLECT_CXX_VER_MINOR       0
#define COLLECT_CXX_VER_PATCH       0
#define COLLECT_CXX_VER_ALPHABETA   1

#define COLLECT_CXX_VER \
    (0\
        |   (   COLLECT_CXX_VER_MAJOR       << 24   ) \
        |   (   COLLECT_CXX_VER_MINOR       << 16   ) \
        |   (   COLLECT_CXX_VER_PATCH       <<  8   ) \
        |   (   COLLECT_CXX_VER_ALPHABETA   <<  0   ) \
    )



#include <cstdint>


namespace collect_cxx {

/** Obtains the value of COLLECT_CXX_VER at the time of compilation of the
 * library.
 */
std::uint32_t
api_version();


} /* namespace collect_cxx */


#pragma once
