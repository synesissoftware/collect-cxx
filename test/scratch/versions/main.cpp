/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.cpp
 *
 * Purpose: Prints collect-cxx composite version and efferent dependencies.
 *
 * Created: 17th September 2026
 * Updated: 27th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <collect-cxx/common.hpp>

#ifdef HAS_BDUT
# include <bdut/bdut.h>
#endif

#ifdef HAS_Diagnosticism
# include <diagnosticism/diagnosticism.h>
# include <diagnosticism/version_string.h>
#endif

#ifdef HAS_STLSoft
# include <stlsoft/stlsoft.h>
#endif

#include <iomanip>
#include <iostream>

#include <stdlib.h>


template<
    typename T_stream
,   typename T_integer
>
void
version(
    T_stream&   stm
,   char const* prefix
,   char const* libname
,   char const* macroname
,   T_integer   libver
)
{
#ifdef HAS_Diagnosticism

    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string(
        buffer
    ,   sizeof(buffer) / sizeof(buffer[0])
    ,   (int)((libver >> 24) & 0xff)
    ,   (int)((libver >> 16) & 0xff)
    ,   (int)((libver >> 8) & 0xff)
    ,   (int)((libver >> 0) & 0xff)
    ,   &n
    );

    if (0 == r)
    {
        buffer[n] = '\0';

        stm
            << prefix
            << libname
            << ": "
            << buffer
            << " ("
            << macroname
            << " = 0x"
            << std::hex << std::setfill('0') << std::setw(8)
            << static_cast<unsigned>(libver)
            << std::dec
            << ")"
            << std::endl
            ;

        return;
    }
#endif /* HAS_Diagnosticism */

    stm
        << prefix
        << libname
        << ": v"
        << ((libver >> 24) & 0xff)
        << '.'
        << ((libver >> 16) & 0xff)
        << '.'
        << ((libver >> 8) & 0xff)
        << '.'
        << ((libver >> 0) & 0xff)
        << " ("
        << macroname
        << " = 0x"
        << std::hex << std::setfill('0') << std::setw(8)
        << static_cast<unsigned>(libver)
        << std::dec
        << ")"
        << std::endl
        ;
}


int main(int /* argc */, char* /* argv */[])
{
    int efferents_count = 0;

    {
        unsigned const libver = COLLECT_CXX_VER;

        version(std::cout, "", "collect-cxx", "COLLECT_CXX_VER", libver);
    }

#ifdef HAS_BDUT

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = BDUT_VER;

        version(std::cout, "\t", "BDUT", "BDUT_VER", libver);
    }
#endif

#ifdef HAS_Diagnosticism

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = DIAGNOSTICISM_VER;

        version(std::cout, "\t", "Diagnosticism", "DIAGNOSTICISM_VER", libver);
    }
#endif

#ifdef HAS_STLSoft

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = _STLSOFT_VER;

        version(std::cout, "\t", "STLSoft", "_STLSOFT_VER", libver);
    }
#endif

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */
