/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.slist-vec/entry.cpp
 *
 * Purpose: Unit-tests for `collect_cxx::slist_vec`.
 *
 * Created: 18th January 2025
 * Updated: 18th January 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <collect-cxx/slist-vec.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <forward_list>
#include <numeric>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    void TEST_ctor_default();
    void TEST_ctor_init_list_1();
    void TEST_ctor_init_list_2();

    void TEST_erase_after_1();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.slist-vec", verbosity))
    {
        XTESTS_RUN_CASE(TEST_ctor_default);
        XTESTS_RUN_CASE(TEST_ctor_init_list_1);
        XTESTS_RUN_CASE(TEST_ctor_init_list_2);

        XTESTS_RUN_CASE(TEST_erase_after_1);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

void TEST_ctor_default()
{
    {
        std::forward_list<int>      c;

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c;

        TEST_INTEGER_EQUAL(0, c.capacity());
        TEST_BOOLEAN_TRUE(c.empty());
        TEST_INTEGER_EQUAL(0, c.size());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_ctor_init_list_1()
{
    {
        std::forward_list<int>      c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_ctor_init_list_2()
{
    {
        std::forward_list<int>      c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(225, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_INTEGER_EQUAL(12, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(50, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(225, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_INTEGER_EQUAL(2, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(60, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(270, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1 };

        TEST_INTEGER_EQUAL(0, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(62, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(271, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_erase_after_1()
{
    {
        std::forward_list<int>      c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#if 0

        auto i3 = std::next(c.begin(), 3);
#else

        auto i3 = c.begin(); ++i3; ++i3; ++i3;
#endif

        c.erase_after(i3);

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(41, std::accumulate(c.begin(), c.end(), 0));
    }

#if 0

    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#if 0

        auto i3 = std::next(c.begin(), 3);
#else

        auto i3 = c.begin(); ++i3; ++i3; ++i3;
#endif

        c.erase_after(i3);

        TEST_INTEGER_EQUAL(22, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(9, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(44, std::accumulate(c.begin(), c.end(), 0));
    }
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

