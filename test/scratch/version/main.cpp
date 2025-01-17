
#include <collect-cxx/common.hpp>

#include <iomanip>
#include <iostream>

#include <cstdlib>


int main(int /* argc */, char* /* argv */[])
{
    auto const version = collect_cxx::api_version();

    std::cout
        << "version:" << '\t' << "0x" << std::setw(8) << std::hex <<std::setfill('0') << version << std::endl
        << "v major:" << '\t' << ((version & 0xff000000) >> 24) << std::endl
        << "v minor:" << '\t' << ((version & 0x00ff0000) >> 16) << std::endl
        << "v patch:" << '\t' << ((version & 0x0000ff00) >> 8) << std::endl
        << "v alpbet:" << '\t' << ((version & 0x000000ff) >> 0) << std::endl
        << std::endl;

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

