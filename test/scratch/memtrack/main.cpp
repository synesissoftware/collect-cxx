
#include <collect-cxx/common.hpp>

#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <typeinfo>
#include <vector>

#include <cstdlib>


template <typename T_container>
void test_()
{
    typedef T_container                                     container_t;

    std::cout << typeid(container_t).name() << ':' << std::endl;


    std::cout << '\t' << "construct (default):" << std::endl;
    {
        container_t c;
    }


    std::cout << '\t' << "construct (init-list):" << std::endl;
    {
        container_t c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    }


    std::cout << '\t' << "construct (copy):" << std::endl;
    {
        container_t c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        container_t c1(c0);
    }


    std::cout << '\t' << "construct (move):" << std::endl;
    {
        container_t c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        container_t c1(std::move(c0));
    }


    std::cout << std::endl;
}


int main(int /* argc */, char* /* argv */[])
{
    test_<std::deque<int>>();
    test_<std::forward_list<int>>();
    test_<std::list<int>>();
    test_<std::vector<int>>();

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

