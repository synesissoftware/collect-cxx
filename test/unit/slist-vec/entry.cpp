/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.slist-vec/entry.cpp
 *
 * Purpose: Unit-tests for `collect_cxx::slist_vec`.
 *
 * Created: 18th January 2025
 * Updated: 19th January 2025
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
    void TEST_ctor_copy_1();
    void TEST_ctor_copy_2();
    void TEST_ctor_move_1();
    void TEST_ctor_move_2();

    void TEST_swap_1();
    void TEST_swap_2();
    void TEST_swap_3();
    void TEST_swap_4();

    void TEST_assign_copy_1();
    void TEST_assign_copy_2();
    void TEST_assign_copy_3();
    void TEST_assign_copy_4();

    void TEST_clear_THEN_assign_1();

    void TEST_erase_after_p_1();
    void TEST_erase_after_p_2();
    void TEST_erase_after_fl_1();
    void TEST_erase_after_fl_2();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace
{
    template <typename T_iterator>
    T_iterator
    call_next(
        T_iterator      i
    ,   std::ptrdiff_t  n
    )
    {
#if 0

        return std::next(i, n);
#else

        for (; 0 != n; --n)
        {
            ++i;
        }

        return i;
#endif
    }

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
        XTESTS_RUN_CASE(TEST_ctor_copy_1);
        XTESTS_RUN_CASE(TEST_ctor_copy_2);
        XTESTS_RUN_CASE(TEST_ctor_move_1);
        XTESTS_RUN_CASE(TEST_ctor_move_2);

        XTESTS_RUN_CASE(TEST_swap_1);
        XTESTS_RUN_CASE(TEST_swap_2);
        XTESTS_RUN_CASE(TEST_swap_3);
        XTESTS_RUN_CASE(TEST_swap_4);

        XTESTS_RUN_CASE(TEST_assign_copy_1);
        XTESTS_RUN_CASE(TEST_assign_copy_2);
        XTESTS_RUN_CASE(TEST_assign_copy_3);
        XTESTS_RUN_CASE(TEST_assign_copy_4);

        XTESTS_RUN_CASE(TEST_clear_THEN_assign_1);

        XTESTS_RUN_CASE(TEST_erase_after_p_1);
        XTESTS_RUN_CASE(TEST_erase_after_p_2);
        XTESTS_RUN_CASE(TEST_erase_after_fl_1);
        XTESTS_RUN_CASE(TEST_erase_after_fl_2);

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

void TEST_ctor_copy_1()
{
    {
        std::forward_list<int>      c0;
        std::forward_list<int>      c(c0);

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0;
        collect_cxx::slist_vec<int> c(c0);

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_ctor_copy_2()
{
    {
        std::forward_list<int>      c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::forward_list<int>      c(c0);

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        collect_cxx::slist_vec<int> c(c0);

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_ctor_move_1()
{
    {
        std::forward_list<int>      c0;
        std::forward_list<int>      c(std::move(c0));

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0;
        collect_cxx::slist_vec<int> c(std::move(c0));

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_ctor_move_2()
{
    {
        std::forward_list<int>      c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::forward_list<int>      c(std::move(c0));

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        collect_cxx::slist_vec<int> c(std::move(c0));

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));


        TEST_BOOLEAN_TRUE(c0.empty());
        TEST_INTEGER_EQUAL(0, c0.size());

        TEST_EQ(c0.cend(), c0.cbegin());
        TEST_EQ(c0.end(), c0.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c0.begin(), c0.end(), 0));
    }
}

void TEST_swap_1()
{
    {
        std::forward_list<int>      c1;
        std::forward_list<int>      c2;

        TEST_BOOLEAN_TRUE(c1.empty());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_TRUE(c1.empty());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c1;
        collect_cxx::slist_vec<int> c2;

        TEST_BOOLEAN_TRUE(c1.empty());
        TEST_INTEGER_EQUAL(0, c1.size());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());
        TEST_INTEGER_EQUAL(0, c2.size());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_TRUE(c1.empty());
        TEST_INTEGER_EQUAL(0, c1.size());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());
        TEST_INTEGER_EQUAL(0, c2.size());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));
    }
}

void TEST_swap_2()
{
    {
        std::forward_list<int>      c1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::forward_list<int>      c2;

        TEST_BOOLEAN_FALSE(c1.empty());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_TRUE(c1.empty());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c2.begin(), c2.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        collect_cxx::slist_vec<int> c2;

        TEST_BOOLEAN_FALSE(c1.empty());
        TEST_INTEGER_EQUAL(10, c1.size());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());
        TEST_INTEGER_EQUAL(0, c2.size());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_TRUE(c1.empty());
        TEST_INTEGER_EQUAL(0, c1.size());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());
        TEST_INTEGER_EQUAL(10, c2.size());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c2.begin(), c2.end(), 0));
    }
}

void TEST_swap_3()
{
    {
        std::forward_list<int>      c1;
        std::forward_list<int>      c2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_TRUE(c1.empty());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_FALSE(c1.empty());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c1;
        collect_cxx::slist_vec<int> c2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_TRUE(c1.empty());
        TEST_INTEGER_EQUAL(0, c1.size());

        TEST_EQ(c1.cend(), c1.cbegin());
        TEST_EQ(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());
        TEST_INTEGER_EQUAL(10, c2.size());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_FALSE(c1.empty());
        TEST_INTEGER_EQUAL(10, c1.size());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_TRUE(c2.empty());
        TEST_INTEGER_EQUAL(0, c2.size());

        TEST_EQ(c2.cend(), c2.cbegin());
        TEST_EQ(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c2.begin(), c2.end(), 0));
    }
}

void TEST_swap_4()
{
    {
        std::forward_list<int>      c1 = { 123, 456, 789 };
        std::forward_list<int>      c2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_FALSE(c1.empty());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(1368, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_FALSE(c1.empty());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(1368, std::accumulate(c2.begin(), c2.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c1 = { 123, 456, 789 };
        collect_cxx::slist_vec<int> c2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_FALSE(c1.empty());
        TEST_INTEGER_EQUAL(3, c1.size());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(1368, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());
        TEST_INTEGER_EQUAL(10, c2.size());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c2.begin(), c2.end(), 0));

        c1.swap(c2);

        TEST_BOOLEAN_FALSE(c1.empty());
        TEST_INTEGER_EQUAL(10, c1.size());

        TEST_NE(c1.cend(), c1.cbegin());
        TEST_NE(c1.end(), c1.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c1.begin(), c1.end(), 0));

        TEST_BOOLEAN_FALSE(c2.empty());
        TEST_INTEGER_EQUAL(3, c2.size());

        TEST_NE(c2.cend(), c2.cbegin());
        TEST_NE(c2.end(), c2.begin());
        TEST_INTEGER_EQUAL(1368, std::accumulate(c2.begin(), c2.end(), 0));
    }
}

void TEST_assign_copy_1()
{
    {
        std::forward_list<int>      c0;
        std::forward_list<int>      c;

        c = c0;

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0;
        collect_cxx::slist_vec<int> c;

        c = c0;

        TEST_INTEGER_EQUAL(0, c.capacity());
        TEST_BOOLEAN_TRUE(c.empty());
        TEST_INTEGER_EQUAL(0, c.size());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_assign_copy_2()
{
    {
        std::forward_list<int>      c0;
        std::forward_list<int>      c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        c = c0;

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0;
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        c = c0;

        TEST_INTEGER_EQUAL(31, c.capacity());
        TEST_BOOLEAN_TRUE(c.empty());
        TEST_INTEGER_EQUAL(0, c.size());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_assign_copy_3()
{
    {
        std::forward_list<int>      c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::forward_list<int>      c;

        c = c0;

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        collect_cxx::slist_vec<int> c;

        c = c0;

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_assign_copy_4()
{
    {
        std::forward_list<int>      c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::forward_list<int>      c = { 123, 456, 789 };

        c = c0;

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        collect_cxx::slist_vec<int> c = { 123, 456, 789 };

        c = c0;

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_clear_THEN_assign_1()
{
    {
        std::forward_list<int>      c = { 123, 456, 789 };

        c.clear();

        c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }

    {
        collect_cxx::slist_vec<int> c = { 123, 456, 789 };

        c.clear();

        c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(45, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_erase_after_p_1()
{
    // std::forward_list<int>
    {
        {
            std::forward_list<int>  c;

            // each of the following is UB

            // c.erase_after(c.before_begin());
            // c.erase_after(c.begin());
        }

    }

    {
        std::forward_list<int>      c = { 1234, 6789 };

        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(8023, std::accumulate(c.begin(), c.end(), 0));

        auto i = c.erase_after(c.begin());

        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(1234, std::accumulate(c.begin(), c.end(), 0));

        TEST_EQ(c.end(), i);

#if 0 // std::forward_list can't do this

        c.erase_after(c.begin());

        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(1234, std::accumulate(c.begin(), c.end(), 0));
#endif
    }

    {
        collect_cxx::slist_vec<int> c = { 1234, 6789 };

        TEST_INTEGER_EQUAL(29, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(2, c.size());
        TEST_INTEGER_EQUAL(8023, std::accumulate(c.begin(), c.end(), 0));

        c.erase_after(c.begin());

        TEST_INTEGER_EQUAL(30, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(1, c.size());
        TEST_INTEGER_EQUAL(1234, std::accumulate(c.begin(), c.end(), 0));

        c.erase_after(c.begin());

        TEST_INTEGER_EQUAL(30, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(1, c.size());
        TEST_INTEGER_EQUAL(1234, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_erase_after_p_2()
{
    {
        std::forward_list<int>      c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto i3 = call_next(c.begin(), 3);

        auto i = c.erase_after(i3);

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(41, std::accumulate(c.begin(), c.end(), 0));

        TEST_NE(c.end(), i);
        TEST_INTEGER_EQUAL(5, *i);
    }

    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        TEST_INTEGER_EQUAL(21, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(10, c.size());


        auto i3 = call_next(c.begin(), 3);

        c.erase_after(i3);

        TEST_INTEGER_EQUAL(22, c.capacity());
        TEST_BOOLEAN_FALSE(c.empty());
        TEST_INTEGER_EQUAL(9, c.size());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(41, std::accumulate(c.begin(), c.end(), 0));
    }
}

void TEST_erase_after_fl_1()
{

}

void TEST_erase_after_fl_2()
{
    {
        std::forward_list<int>      c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
/*
                                                ^              ^
                                          0, 1, 2,             7, 8, 9
*/

        auto i2 = call_next(c.begin(), 2);
        auto i7 = call_next(c.begin(), 7);

        auto i = c.erase_after(i2, i7);

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(27, std::accumulate(c.begin(), c.end(), 0));

        TEST_NE(c.end(), i);
        TEST_INTEGER_EQUAL(7, *i);


        auto ib = call_next(c.before_begin(), 0);
        auto i6 = call_next(c.begin(), 6);

        auto e = c.erase_after(ib, i6);

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));

        TEST_EQ(c.end(), e);
    }


    {
        collect_cxx::slist_vec<int> c = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
/*
                                                ^              ^
                                          0, 1, 2,             7, 8, 9
*/

        auto i2 = call_next(c.begin(), 2);
        auto i7 = call_next(c.begin(), 7);

        /*auto i =*/ c.erase_after(i2, i7);

        TEST_BOOLEAN_FALSE(c.empty());

        TEST_NE(c.cend(), c.cbegin());
        TEST_NE(c.end(), c.begin());
        TEST_INTEGER_EQUAL(27, std::accumulate(c.begin(), c.end(), 0));

        // TEST_NE(c.end(), i);
        // TEST_INTEGER_EQUAL(7, *i);

        auto ib = call_next(c.before_begin(), 0);
        auto i6 = call_next(c.begin(), 6);

        /*auto e =*/ c.erase_after(ib, i6);

        TEST_BOOLEAN_TRUE(c.empty());

        TEST_EQ(c.cend(), c.cbegin());
        TEST_EQ(c.end(), c.begin());
        TEST_INTEGER_EQUAL(0, std::accumulate(c.begin(), c.end(), 0));

        // TEST_EQ(c.end(), e);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

