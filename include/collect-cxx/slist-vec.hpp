/* /////////////////////////////////////////////////////////////////////////
 * File:    include/collect-cxx/slist-vec.hpp
 *
 * Purpose: Definition of the `collect_cxx::slist_vec<>` class template.
 *
 * Created: 18th January 2025
 * Updated: 19th January 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <collect-cxx/common.hpp>

#include <array>
#include <list>
#include <memory>
#include <type_traits>

#include <cassert>


namespace collect_cxx {


/** T.B.C.
 *
 * @tparam T_value The value type;
 * @tparam T_allocator The allocator type, which defaults to
 *  std::allocator<T_value>;
 */
template<
    typename T_value
,   typename T_allocator = std::allocator<T_value>
>
class slist_vec
    : private T_allocator
{
public: // types
    /// The current specialisation of the type.
    typedef slist_vec<
        T_value
    ,   T_allocator
    >                                                       class_type;
#ifndef COLLECT_CXX_DOCUMENTATION_SKIP_SECTION
    typedef class_type                                      container_type;
#endif /* !COLLECT_CXX_DOCUMENTATION_SKIP_SECTION */
    /// The value type.
    typedef T_value                                         value_type;
    /// The allocator type.
    typedef T_allocator                                     allocator_type;
    /// The allocator traits type.
    typedef std::allocator_traits<allocator_type>           allocator_traits_type;
    /// The mutable (non-const) reference type.
    typedef value_type&                                     reference;
    /// The non-mutable (const) reference type.
    typedef value_type const&                               const_reference;
    /// The difference type.
    typedef std::ptrdiff_t                                  difference_type;
    /// The size type.
    typedef std::size_t                                     size_type;
private:
    struct block;
    struct entry
    {
//      entry*      prev;
        entry*      next;
        block*      block;
        value_type  value;
    };
    struct block
    {
    private:
        friend class slist_vec<T_value, T_allocator>;

    public: // fields
        size_type               num_used;
//      std::array<entry, 20>   entries;
        std::array<entry, 31>   entries;

    public: // construction
        block();

    public: // attributes
        size_type capacity() const noexcept;
        size_type size() const noexcept;
        bool empty() const noexcept;
        bool full() const noexcept;
    };
    typedef typename allocator_traits_type::template rebind_alloc<
        block
    >                                                       block_ator_type_;
    typedef std::list<
        block
    ,   block_ator_type_
    >                                                       block_list_type_;
public:
    /// The non-mutating (const) iterator type.
    class const_iterator
    {
    private:
        friend class slist_vec<T_value, T_allocator>;

    public: // types
        typedef typename container_type::difference_type        difference_type;

    public: // construction
        const_iterator(
            entry*          pentry
        ,   entry const*    pend
        )
            : m_pentry(pentry)
            , m_pend(pend)
        {}


    public: // comparison
        bool equal(const_iterator const& rhs) const noexcept
        {
            assert(m_pend == rhs.m_pend);

            return m_pentry == rhs.m_pentry;
        }
#if 1

        bool operator ==(const_iterator const& rhs) const noexcept
        {
            return equal(rhs);
        }
#endif
#if 0

        bool operator !=(const_iterator const& rhs) const noexcept
        {
            return !equal(rhs);
        }
#endif


    public: // iteration
        value_type const& operator *() const
        {
            assert(m_pentry != m_pend);

            return m_pentry->value;
        }

        const_iterator& operator ++()
        {
            m_pentry = m_pentry->next;

            return *this;
        }


    private: // attributes
        entry const*    entry_() const noexcept
        {
            return m_pentry;
        }
        entry*          entry_() noexcept
        {
            return m_pentry;
        }

    private: // fields
        entry*              m_pentry;
        entry const* const  m_pend;
    };


public: // construction
    /// Default constructor.
    slist_vec();
    /// Constructs an instance containing the elements provide by ilist.
    slist_vec(std::initializer_list<value_type> ilist);
    /// @brief T.B.C.
    /// @param T.B.C.
    slist_vec(class_type const&);
    /// @brief T.B.C.
    /// @param T.B.C.
    slist_vec(class_type&&);
    /// @brief T.B.C.
    /// @param T.B.C.
    class_type& operator =(class_type const&);
    /// @brief T.B.C.
    /// @param T.B.C.
    class_type& operator =(std::initializer_list<value_type> ilist);

    /// @brief Returns the allocator associated with the instance.
    allocator_type get_allocator() const;

    /// @brief Exchanges the contents of the instance with rhs.
    ///
    /// @param rhs The instance with which to exchange.
    void swap(class_type& rhs) noexcept;

public: // attributes
    /// @brief Indicates the number of elements for which the instance is
    ///  holding space that would not require further allocation.
    size_type capacity() const noexcept;
    /// @brief Indicates the number of elements in the instance.
    size_type size() const noexcept;
    /// @brief Indicates whether the instance is empty.
    bool empty() const noexcept;


public: // modifiers
    /// T.B.C.
    ///
    /// Erases all elements from the instance, but does not clear underlying
    /// blocks.
    void clear() noexcept;

    /// T.B.C.
    ///
    /// @param pos A valid iterator refering to an element after which a
    ///  single element, if present, is to be removed;
    ///
    /// @pre !empty()
    void
    erase_after(
        const_iterator  pos
    );

    /// T.B.C.
    ///
    /// @pre !empty()
    /// @pre from != to
    /// @pre from != end()
    void
    erase_after(
        const_iterator  from
    ,   const_iterator  to
    );

    void push_back(value_type const& value);
    void push_back(value_type&& value);


public: // iteration
    /// Returns a pseudo-iterator to the element before the first element in
    /// the instance. This element acts as a placeholder only - attempting
    /// to dereference it results in undefined behavior. The only valid uses
    /// are to pass it to functions insert_after(), emplace_after(),
    /// erase_after(), splice_after() and to invoke its increment operator:
    /// incrementing the before-begin iterator gives exactly the same
    /// iterator as obtained from begin()/cbegin().
    const_iterator
    cbefore_begin() const;
    /// @see cbefore_begin
    const_iterator
    before_begin() const;

    const_iterator
    cbegin() const;
    const_iterator
    cend() const;
    const_iterator
    begin() const;
    const_iterator
    end() const;


public: // element access
    /// @brief Mutating (non-const) reference to the first element in the
    ///  instance.
    ///
    /// @pre !empty()
    reference front() noexcept;
    /// @brief Non-utating (const) reference to the first element in the
    ///  instance.
    ///
    /// @pre !empty()
    const_reference front() const noexcept;
    /// @brief Mutating (non-const) reference to the last element in the
    ///  instance.
    ///
    /// @pre !empty()
    reference back() noexcept;
    /// @brief Non-utating (const) reference to the last element in the
    ///  instance.
    ///
    /// @pre !empty()
    const_reference back() const noexcept;

private: // implementation
    // Gives the before-begin pointer, obtaining the anchoring entry
    entry*
    bbegin_() const noexcept;
    // Gives the end pointer, obtaining a non-usable entry
    entry*
    end_() const noexcept;

    /*
    0 entries:
     bb | e

    1 entry:
     bb | 0 | e

    4 entries:
     bb | 0 | 1 | 2 | 3 | e
    */

    void
    clear_without_dropping_blocks_() noexcept;

    struct block&
    push_new_initialised_block_();


private: // fields
    size_type           m_capacity;     // capacity
    size_type           m_size;         // size
#if 0

    block_list_type_    m_active_block_list;
    block_list_type_    m_spare_block_list;
#else

    block_list_type_    m_block_list;   // blocks
#endif
    struct entry        m_bbegin;       // special entry holding first block in list, and able to provide before_begin
    entry*              m_last;         // pointer to the last block in the list
};


// operators

#if 0

template <typename T_value, typename T_allocator>
bool
operator ==(
    typename slist_vec<T_value, T_allocator>::const_iterator const& lhs
,   typename slist_vec<T_value, T_allocator>::const_iterator const& rhs
) noexcept
{
    return lhs.equal(rhs);
}
#endif

template <typename T_value, typename T_allocator>
bool
operator !=(
    typename slist_vec<T_value, T_allocator>::const_iterator const& lhs
,   typename slist_vec<T_value, T_allocator>::const_iterator const& rhs
) noexcept
{
    return !lhs.equal(rhs);
}


// slist_vec<>::block

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::block::block()
    : num_used(0)
    , entries()
{}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::size_type
slist_vec<T_value, T_allocator>::block::capacity() const noexcept
{
    return entries.size() - num_used;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::size_type
slist_vec<T_value, T_allocator>::block::size() const noexcept
{
    return num_used;
}

template <typename T_value, typename T_allocator>
bool
slist_vec<T_value, T_allocator>::block::empty() const noexcept
{
    return 0 == size();
}

template <typename T_value, typename T_allocator>
bool
slist_vec<T_value, T_allocator>::block::full() const noexcept
{
    return 0 == capacity();
}


// slist_vec<> : implementation

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::entry*
slist_vec<T_value, T_allocator>::bbegin_() const noexcept
{
    return const_cast<entry*>(&m_bbegin);
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::entry*
slist_vec<T_value, T_allocator>::end_() const noexcept
{
    return reinterpret_cast<entry*>(const_cast<class_type*>(this));
}

template <typename T_value, typename T_allocator>
void
slist_vec<T_value, T_allocator>::clear_without_dropping_blocks_() noexcept
{
    for (struct entry*& e = bbegin_()->next; end_() != e; )
    {
        struct entry* next = e->next;

        assert(nullptr != e->next);
        assert(nullptr != e->block);

        e->value = value_type();
        e->next = nullptr;

        e = next;

        --m_size;
        ++m_capacity;
    }
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::block&
slist_vec<T_value, T_allocator>::push_new_initialised_block_()
{
    m_block_list.push_back(block());

    struct block& last_block = m_block_list.back();

    for (struct entry& e : last_block.entries)
    {
        e.block = &last_block;
    }

    m_capacity += last_block.capacity();

    return last_block;
}


// slist_vec<> : construction

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::slist_vec()
    : m_capacity(0)
    , m_size(0)
#if 0

    , m_active_block_list()
    , m_spare_block_list()
#else

    , m_block_list()
#endif
    , m_bbegin({ end_(), nullptr, value_type() })
    , m_last(end_())
{}

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::slist_vec(std::initializer_list<value_type> ilist)
    : m_capacity(0)
    , m_size(0)
#if 0

    , m_active_block_list()
    , m_spare_block_list()
#else

    , m_block_list()
#endif
    , m_bbegin({ end_(), nullptr, value_type() })
    , m_last(end_())
{
    for (value_type const& value : ilist)
    {
        push_back(value);
    }
}

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::slist_vec(class_type const& rhs)
    : m_capacity(0)
    , m_size(0)
    , m_block_list()
    , m_bbegin({ end_(), nullptr, value_type() })
    , m_last(end_())
{
    for (value_type const& value : rhs)
    {
        push_back(value);
    }
}

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::slist_vec(class_type&& rhs)
    : m_capacity()
    , m_size()
    , m_block_list()
    , m_bbegin({ end_(), nullptr, value_type() })
    , m_last(end_())
{
    swap(rhs);
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::class_type&
slist_vec<T_value, T_allocator>::slist_vec::operator =(class_type const& rhs)
{
    clear_without_dropping_blocks_();

    for (value_type const& value : rhs)
    {
        push_back(value);
    }

    return *this;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::class_type&
slist_vec<T_value, T_allocator>::slist_vec::operator =(std::initializer_list<value_type> ilist)
{
    // as an optimisation we now ensure to obtain all requisite blocks for
    // the known size of elements

    clear_without_dropping_blocks_();

    while (ilist.size() > capacity())
    {
        push_new_initialised_block_();
    }

    // for each item in ilist add into ready block(s)

    auto    it_block    =   m_block_list.begin();
    auto    it_values   =   ilist.begin();

    for (size_type n = 0; ilist.end() != it_values; ++it_values)
    {
        struct block&       blk             =   *it_block;

        std::size_t const   index_in_block  =   n;

        struct entry&       e               =   blk.entries[index_in_block];

        e.next  =   end_();
        e.block =   &blk;
        e.value =   *it_values;

        if (empty())
        {
            m_bbegin.next   =   &e;
        }
        else
        {
            m_last->next    =   &e;
        }

        m_last = &e;

        ++blk.num_used;

        if (++n == blk.entries.size())
        {
            ++it_block;

            n = 0;
        }

        --m_capacity;
        ++m_size;
    }

    return *this;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::allocator_type
slist_vec<T_value, T_allocator>::get_allocator() const
{
    return allocator_type(*this);
}

template <typename T_value, typename T_allocator>
void
slist_vec<T_value, T_allocator>::swap(class_type& rhs) noexcept
{
    struct entry* const rhs_e   =   rhs.end_();
    struct entry* const this_e  =   this->end_();


    // m_capacity is normal

    std::swap(m_capacity, rhs.m_capacity);


    // m_size is normal

    std::swap(m_size, rhs.m_size);


    // m_block_list is normal, except any `next` fields referring to
    // `end_()` in either list must be swapped to ensure that they are still
    // correct within their new containing instance

    std::swap(m_block_list, rhs.m_block_list);

    for (auto& block : m_block_list)
    {
        for (auto& entry : block.entries)
        {
            if (rhs_e == entry.next)
            {
                entry.next = this_e;
            }
        }
    }
    for (auto& block : rhs.m_block_list)
    {
        for (auto& entry : block.entries)
        {
            if (this_e == entry.next)
            {
                entry.next = rhs_e;
            }
        }
    }


    // m_bbegin is normal, except need to account for `end_()` pointers

    std::swap(m_bbegin, rhs.m_bbegin);
    if (rhs_e == m_bbegin.next)
    {
        m_bbegin.next = this_e;
    }
    if (this_e == rhs.m_bbegin.next)
    {
        rhs.m_bbegin.next = rhs_e;
    }


    // m_size is normal, except need to account for `end_()` pointers

    std::swap(m_last, rhs.m_last);
    if (rhs_e == m_last)
    {
        m_last = this_e;
    }
    if (this_e == rhs.m_last)
    {
        rhs.m_last = rhs_e;
    }
}


// slist_vec<> : attributes

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::size_type
slist_vec<T_value, T_allocator>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::size_type
slist_vec<T_value, T_allocator>::size() const noexcept
{
    return m_size;
}

template <typename T_value, typename T_allocator>
bool
slist_vec<T_value, T_allocator>::empty() const noexcept
{
    return 0 == size();
}


// slist_vec<> : iteration

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::cbefore_begin() const
{
    return const_iterator(bbegin_(), end_());
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::before_begin() const
{
    return cbefore_begin();
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::cbegin() const
{
    return const_iterator(m_bbegin.next, end_());
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::cend() const
{
    return const_iterator(end_(), end_());
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::begin() const
{
    return cbegin();
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::end() const
{
    return cend();
}


// slist_vec<> : element access

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::reference
slist_vec<T_value, T_allocator>::front() noexcept
{
    assert(!empty());
    assert(end_() != m_bbegin.next);

    return m_bbegin.next->value;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_reference
slist_vec<T_value, T_allocator>::front() const noexcept
{
    assert(!empty());
    assert(end_() != m_bbegin.next);

    return m_bbegin.next->value;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::reference
slist_vec<T_value, T_allocator>::back() noexcept
{
    assert(!empty());
    assert(end_() != m_last);

    return m_last->value;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_reference
slist_vec<T_value, T_allocator>::back() const noexcept
{
    assert(!empty());
    assert(end_() != m_last);

    return m_last->value;
}


// slist_vec<> : modifiers

template <typename T_value, typename T_allocator>
void
slist_vec<T_value, T_allocator>::clear() noexcept
{
    clear_without_dropping_blocks_();
}

template <typename T_value, typename T_allocator>
void
slist_vec<T_value, T_allocator>::erase_after(
    const_iterator  pos
)
{
    assert(end() != pos);

    struct entry* const e_ref   =   pos.entry_();
    struct entry* const e_next  =   e_ref->next;

    if (end_() == e_next)
    {
        // return end();
    }
    else
    {
        // need to:
        //
        // - "remove" e_next from the list, tying e_ref to e_next->next
        // - "reset" e_next
        // - adjust the block attributes
        // - adjust the container attributes

        struct block* const b_next = e_next->block;


        e_ref->next     =   e_next->next;

        e_next->value   =   value_type();
        e_next->next    =   nullptr; // this marks the element as unused

        --b_next->num_used;

        ++m_capacity;
        --m_size;

        if (b_next->empty())
        {
            // TODO: free, or put onto spare list
        }
    }
}

template <typename T_value, typename T_allocator>
void
// iterator
slist_vec<T_value, T_allocator>::erase_after(
    const_iterator  from
,   const_iterator  to
)
{
    assert(end() != from);
    assert(to != from); // this violates the contract

    if (from == to)
    {
        // return ???;
    }
    else
    {
        struct entry* const e_ref   =   from.entry_();
        struct entry*       e_next  =   e_ref->next;

        struct entry* const e_to    =   to.entry_();

        assert(e_to != e_ref);

        if (e_next == e_to)
        {
            // return ???;
        }
        else
        {
            for ( ; e_to != e_next; )
            {
                struct entry* const e_curr = e_next;

                struct block* const b_curr = e_curr->block;

                e_ref->next     =   e_curr->next;
                e_next          =   e_curr->next;

                e_curr->value   =   value_type();
                e_curr->next    =   nullptr; // this marks the element as unused

                --b_curr->num_used;

                if (b_curr->empty())
                {
                    // TODO: free, or put onto spare list
                }

                ++m_capacity;
                --m_size;
            }
        }
    }
}

template <typename T_value, typename T_allocator>
void
slist_vec<T_value, T_allocator>::push_back(value_type const& value)
{
    struct entry* pe = nullptr;

    if (0 == capacity())
    {
        struct block& last_block = push_new_initialised_block_();

        pe = &last_block.entries[0];
    }
    else
    {
        for (auto& block : m_block_list)
        {
            if (!block.full())
            {
                auto i = std::find_if(
                                block.entries.begin()
                            ,	block.entries.end()
                            ,	[](struct entry& e) {

                                return nullptr == e.next;
                            });

                assert(block.entries.end() != i);

                pe = &*i;

                pe->block = &block;

                break;
            }
        }
    }

    assert(nullptr != pe);

    if (empty())
    {
        m_bbegin.next = pe;
    }
    else
    {
        m_last->next = pe;
    }

    m_last = pe;

    pe->next = end_();
    pe->value = value;

    ++pe->block->num_used;

    --m_capacity;
    ++m_size;

}


} /* namespace collect_cxx */


#pragma once

