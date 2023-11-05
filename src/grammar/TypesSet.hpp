#ifndef TYPESSET_HPP
#define TYPESSET_HPP

#include <unordered_set>

template < typename T, typename Hash >
class TypesSet
{
    using InternalSet = std::unordered_set< T, Hash >;
    using ClassType = TypesSet< T, Hash >;
    InternalSet m_internal_set;

public:

    typename InternalSet::iterator
    begin( )
    {
        return m_internal_set.begin( );
    }

    typename InternalSet::iterator
    end( )
    {
        return m_internal_set.end( );
    }

    typename InternalSet::const_iterator
    begin( ) const
    {
        return m_internal_set.cbegin( );
    }

    typename InternalSet::const_iterator
    end( ) const
    {
        return m_internal_set.cend( );
    }

    std::pair< typename InternalSet::iterator, bool >
    insert( const typename InternalSet::value_type& value )
    {
        return m_internal_set.insert( value );
    }

    bool
    operator==( const ClassType& other ) const
    {
        return m_internal_set == other.m_internal_set;
    }

    void
    unite_with( const ClassType& other )
    {
        for ( const auto& sequence : other.m_internal_set )
        {
            m_internal_set.insert( sequence );
        }
    }

    bool
    contains( const T& value ) const
    {
        return m_internal_set.count( value ) > 0;
    }

    void
    add_k( const ClassType& other, std::size_t k )
    {
        InternalSet tmp_set;
        if ( m_internal_set.empty( ) )
        {
            for ( const auto& other_sequence : other.m_internal_set )
            {
                insert_k( tmp_set, other_sequence, k );
            }
            m_internal_set = tmp_set;
            return;
        }
        if ( other.m_internal_set.empty( ) )
        {
            for ( const auto& other_sequence : m_internal_set ) {
                insert_k( tmp_set, other_sequence, k );
            }
            m_internal_set = tmp_set;
            return;
        }
        for ( const auto& sequence : m_internal_set )
        {
            for ( const auto& other_sequence : other.m_internal_set )
            {
                if ( sequence.size( ) == 1 && sequence[ 0 ]->is_epsilon( ) )
                {
                    insert_k( tmp_set, other_sequence, k );
                }
                else if ( other_sequence.size( ) == 1 && other_sequence[ 0 ]->is_epsilon( ) )
                {
                    insert_k( tmp_set, sequence, k );
                }
                else
                {
                    auto tmp_sequence = sequence;
                    std::copy( other_sequence.cbegin( ),
                               other_sequence.cend( ),
                               std::back_inserter( tmp_sequence ) );
                    insert_k( tmp_set, tmp_sequence, k );
                }
            }
        }

        m_internal_set = tmp_set;
    }

    std::size_t
    size( ) const
    {
        return m_internal_set.size( );
    }

    const typename InternalSet::value_type&
    operator[]( const typename InternalSet::value_type& value )
    {
        return m_internal_set[ value ];
    }
private:
    void
    insert_k( InternalSet& set, const T& value, std::size_t k )
    {
        T cropped;
        auto end = k >= value.size( ) ? value.cend( ) : value.cbegin( ) + k;
        std::copy( value.cbegin( ), end, std::back_inserter( cropped ) );
        set.insert( cropped );
    }
};

#endif  // TERMINALSSET_HPP
