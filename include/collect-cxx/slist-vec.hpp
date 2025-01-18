
#include <collect-cxx/common.hpp>

#include <array>
#include <list>
#include <memory>
#include <type_traits>

#include <cassert>


namespace collect_cxx {


template<
    typename T_value
,   typename T_allocator = std::allocator<T_value>
>
class slist_vec
    : private T_allocator
{
public: // types
    typedef slist_vec<
        T_value
    ,   T_allocator
    >                                                       class_type;
    typedef class_type                                      container_type;
    typedef T_value                                         value_type;
    typedef T_allocator                                     allocator_type;
    typedef std::allocator_traits<allocator_type>           allocator_traits_type;
    typedef value_type&                                     reference;
    typedef value_type const&                               const_reference;
    typedef std::ptrdiff_t                                  difference_type;
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
        block(value_type const& value, entry* next);
        block(value_type&& value, entry* next);
//      block(std::initializer_list<value_type> ilist);

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
    slist_vec();
    slist_vec(std::initializer_list<value_type>);

    allocator_type get_allocator() const;

    void swap(class_type&) noexcept;

public: // attributes
    size_type capacity() const noexcept;
    size_type size() const noexcept;
    bool empty() const noexcept;


public: // modifiers
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

    void push_back(value_type const& value);
    void push_back(value_type&& value);


public: // iteration
    const_iterator
    cbegin() const;
    const_iterator
    cend() const;
    const_iterator
    begin() const;
    const_iterator
    end() const;


public: // element access
    reference front() noexcept;
    const_reference front() const noexcept;
    reference back() noexcept;
    const_reference back() const noexcept;

private: // implementation
    entry*
    end_() const noexcept;

private: // fields
    size_type           m_capacity;     // capacity
    size_type           m_size;         // size
#if 0

    block_list_type_    m_active_block_list;
    block_list_type_    m_spare_block_list;
#else

    block_list_type_    m_block_list;   // blocks
#endif
    entry*              m_first;        // pointer to the first block in the list
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


// implementation


template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::entry*
slist_vec<T_value, T_allocator>::end_() const noexcept
{
    return reinterpret_cast<entry*>(const_cast<class_type*>(this));
}

#if 1

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::block::block(
    typename slist_vec<T_value, T_allocator>::value_type const& value
,   entry*                                                      next
)
    : num_used(1)
    , entries({ { { next, this, value } } })
{
//	entries[0] = { next, value };

    assert(31 == entries.size());
}
#endif

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

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::slist_vec()
    : m_capacity(0)
    , m_size(0)
    , m_block_list()
    , m_first(nullptr)
    , m_last(nullptr)
{}

template <typename T_value, typename T_allocator>
slist_vec<T_value, T_allocator>::slist_vec(std::initializer_list<value_type> ilist)
    : m_capacity(0)
    , m_size(0)
    , m_block_list()
    , m_first(nullptr)
    , m_last(nullptr)
{
    for (value_type const& value : ilist)
    {
        push_back(value);
    }
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
    std::swap(m_capacity, rhs.m_capacity);
    std::swap(m_size, rhs.m_size);
#if 0

    std::swap(m_active_block_list, rhs.m_active_block_list);
    std::swap(m_spare_block_list, rhs.m_spare_block_list);
#else

    std::swap(m_block_list, rhs.m_block_list);
#endif
    std::swap(m_first, rhs.m_first);
    std::swap(m_last, rhs.m_last);
}


#if 0

slist_vec::block::block(std::initializer_list<int> ilist)
    : num_used(ilist.size())
    , entries(ilist)
{}
#endif

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

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_iterator
slist_vec<T_value, T_allocator>::cbegin() const
{
    if (nullptr == m_first)
    {
        return cend();
    }

    return const_iterator(m_first, end_());
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


template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::reference
slist_vec<T_value, T_allocator>::front() noexcept
{
    assert(!empty());
    assert(nullptr != m_first);

    return m_first->value;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_reference
slist_vec<T_value, T_allocator>::front() const noexcept
{
    assert(!empty());
    assert(nullptr != m_first);

    return m_first->value;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::reference
slist_vec<T_value, T_allocator>::back() noexcept
{
    assert(!empty());
    assert(nullptr != m_last);

    return m_last->value;
}

template <typename T_value, typename T_allocator>
typename slist_vec<T_value, T_allocator>::const_reference
slist_vec<T_value, T_allocator>::back() const noexcept
{
    assert(!empty());
    assert(nullptr != m_last);

    return m_last->value;
}


template <typename T_value, typename T_allocator>
void
slist_vec<T_value, T_allocator>::push_back(value_type const& value)
{
    if (0 == capacity())
    {
        m_block_list.push_back(block(value, end_()));
        //m_block_list.emplace_back(value);

        struct block& last_block = m_block_list.back();

        m_capacity += last_block.capacity();
        m_size += 1;

        struct entry& e = last_block.entries[0];

        if (nullptr == m_first)
        {
            assert(nullptr == m_last);

            m_last = m_first = &e;
        }
        else
        {
            m_last->next = &e;
            m_last = &e;
        }
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

                struct entry& e = *i;

                e.next = end_();
                e.block = &block;
                e.value = value;

                m_last->next = &e;
                m_last = &e;

                block.num_used += 1;

                --m_capacity;
                ++m_size;

                break;
            }
        }
    }
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
    }
}


} /* namespace collect_cxx */


#pragma once

