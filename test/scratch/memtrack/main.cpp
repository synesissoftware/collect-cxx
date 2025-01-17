
#include <collect-cxx/common.hpp>

#include <stlsoft/memory/allocator_base.hpp>

#include <diagnosticism/tracing.h>

#include <deque>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <typeinfo>
#include <vector>

#include <cstdlib>

// #define TRACE_CALLS


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


    std::cout << '\t' << "swap:" << std::endl;
    {
        container_t c0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        container_t c1;

        c0.swap(c1);
    }


    std::cout << std::endl;
}


std::map<void const*, std::size_t>  tracking_numbers;
std::size_t                         running_allocation  =   0;
std::size_t                         total_allocation    =   0;
std::size_t                         num_allocations     =   0;
std::size_t                         num_deallocations   =   0;


template <ss_typename_param_k T>
class tracking_alocator
    : public stlsoft::allocator_base<T, tracking_alocator<T> >
{
private: // types
    typedef stlsoft::allocator_base<T, tracking_alocator<T> >       parent_class_type;
public:
    /// The current specialisation of the type
    typedef tracking_alocator<T>                                    class_type;
    /// The value type
    typedef ss_typename_type_k parent_class_type::value_type        value_type;
    /// The pointer type
    typedef ss_typename_type_k parent_class_type::pointer           pointer;
    /// The non-mutating (const) pointer type
    typedef ss_typename_type_k parent_class_type::const_pointer     const_pointer;
    /// The reference type
    typedef ss_typename_type_k parent_class_type::reference         reference;
    /// The non-mutating (const) reference type
    typedef ss_typename_type_k parent_class_type::const_reference   const_reference;
    /// The difference type
    typedef ss_typename_type_k parent_class_type::difference_type   difference_type;
    /// The size type
    typedef ss_typename_type_k parent_class_type::size_type         size_type;

public:
#ifdef STLSOFT_CF_ALLOCATOR_REBIND_SUPPORT
    /// The allocator's <b><code>rebind</code></b> structure
    template <ss_typename_param_k U>
    struct rebind
    {
        typedef tracking_alocator<U>                                    other;
    };
#endif /* STLSOFT_CF_ALLOCATOR_REBIND_SUPPORT */

public: // construction
    /// Default constructor
    tracking_alocator() STLSOFT_NOEXCEPT
    {}
    /// Copy constructor
#ifdef STLSOFT_CF_ALLOCATOR_REBIND_SUPPORT
    template <ss_typename_param_k U>
    tracking_alocator(tracking_alocator<U> const&)
    {}
#else /* ? STLSOFT_CF_ALLOCATOR_REBIND_SUPPORT */
    tracking_alocator(class_type const&)
    {}
#endif /* STLSOFT_CF_ALLOCATOR_REBIND_SUPPORT */

private: // implementation
    friend class stlsoft::allocator_base<T, tracking_alocator<T> >;

    void* do_allocate(size_type n, void const* hint)
    {
#ifdef TRACE_CALLS

        diagnosticism_trace(stderr, "n=%llu, hint=%p", n, hint);
#endif

        STLSOFT_SUPPRESS_UNUSED(hint);

        void* pv = ::malloc(n * sizeof(value_type));

        if (nullptr != pv)
        {
            auto i = tracking_numbers.find(pv);

            if (tracking_numbers.end() != i)
            {
                fprintf(stderr, "POINTER (%p) ALREADY SEEN!\n", pv);
            }
            else
            {
                tracking_numbers.insert(std::pair(pv, n));
            }

            ++num_allocations;

            running_allocation  +=  n;
            total_allocation    +=  n;
        }

        return pv;
    }
    void do_deallocate(void* pv, size_type n)
    {
#ifdef TRACE_CALLS

        diagnosticism_trace(stderr, "pv=%p, n=%llu", pv, n);
#endif

        STLSOFT_SUPPRESS_UNUSED(n);

        if (nullptr != pv)
        {
            auto i = tracking_numbers.find(pv);

            if (tracking_numbers.end() == i)
            {
                fprintf(stderr, "POINTER (%p) NOT SEEN!\n", pv);
            }
            else
            {
                running_allocation  -=  (*i).second;

                tracking_numbers.erase(i);
            }

            ++num_deallocations;
        }

        ::free(pv);
    }
    void do_deallocate(void* pv)
    {
#ifdef TRACE_CALLS

        diagnosticism_trace(stderr, "pv=%p", pv);
#endif

        ::free(pv);
    }
};


int main(int /* argc */, char* /* argv */[])
{
    typedef tracking_alocator<int>                          int_ator_t;

    test_<std::deque<int, int_ator_t>>();
    test_<std::forward_list<int, int_ator_t>>();
    test_<std::list<int, int_ator_t>>();
    test_<std::vector<int, int_ator_t>>();

    {
        std::cout << std::endl;

        std::cout << "memory tracking:" << std::endl;

        std::cout << '\t' << "#allocations:     " << '\t' << std::setw(10) << std::right<< num_allocations << std::endl;
        std::cout << '\t' << "#deallocations:   " << '\t' << std::setw(10) << std::right<< num_deallocations << std::endl;

        std::cout << '\t' << "total allocated:  " << '\t' << std::setw(10) << std::right<< total_allocation << std::endl;
        std::cout << '\t' << "current allocated:" << '\t' << std::setw(10) << std::right<< running_allocation << std::endl;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

