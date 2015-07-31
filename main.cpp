#include "groupBy.h"

#include <cassert>

struct T
{
    int i;
    float f;
    char c;
};

bool operator==( T const & lhs, T const & rhs )
{
    return lhs.i == rhs.i && lhs.f == rhs.f && lhs.c == rhs.c;
}

int get_i( T const & t )
{
    return t.i;
}

const int & get_cir( T const & t )
{
    return t.i;
}

struct Get_f
{
    float operator()( T const & t ) const
    {
        return t.f;
    }
};

auto const get_c = []( T const & t )
{
    return t.c;
};

int main()
{
    std::vector<T> v{ {
        T{ 1, 1.1f, 'a' },
        T{ 2, 2.2f, 'b' },
        T{ 2, 2.2f, 'c' },
        T{ 3, 3.3f, 'd' },
        T{ 3, 3.3f, 'e' },
        T{ 3, 3.3f, 'f' } } };

    {
        std::map< int, std::vector< T > > const actual = groupBy( v.begin(), v.end(), & get_i );

        std::map< int, std::vector< T > > const expected {
          { { 1,
                { T{ 1, 1.1f, 'a' } } },
            { 2,
                { T{ 2, 2.2f, 'b' }, T{ 2, 2.2f, 'c' } } },
            { 3,
                { T{ 3, 3.3f, 'd' }, T{ 3, 3.3f, 'e' }, T{ 3, 3.3f, 'f' } } } }
        };

        assert( actual == expected );
    }

    {
        std::map< int, std::vector< T > > const actual = groupBy( v.begin(), v.end(), & get_cir );

        std::map< int, std::vector< T > > const expected {
          { { 1,
                { T{ 1, 1.1f, 'a' } } },
            { 2,
                { T{ 2, 2.2f, 'b' }, T{ 2, 2.2f, 'c' } } },
            { 3,
                { T{ 3, 3.3f, 'd' }, T{ 3, 3.3f, 'e' }, T{ 3, 3.3f, 'f' } } } }
        };

        assert( actual == expected );
    }

    {
        std::map< int, std::map< float, std::vector< T > > > const actual
            = groupBy( v.begin(), v.end(), & get_i, Get_f());

        std::map< int, std::map< float, std::vector< T > > > const expected{
            { { 1,
                { { 1.1f,
                    { T{ 1, 1.1f, 'a' } } } } },
              { 2,
                  { { 2.2f,
                    { T{ 2, 2.2f, 'b' }, T{ 2, 2.2f, 'c' } } } } },
              { 3,
                { { 3.3f,
                    { T{ 3, 3.3f, 'd' }, T{ 3, 3.3f, 'e' }, T{ 3, 3.3f, 'f' } } } } } }
        };

        assert( actual == expected );
    }

    {
        std::map< int, std::map<float, std::map<char, std::vector<T> > > > const actual
            = groupBy( v.begin(), v.end(), & get_i, Get_f(), get_c );

        std::map< int, std::map< float, std::map< char, std::vector< T > > > > const expected {
            { { 1,
                { { 1.1f,
                    { { 'a', { T{ 1, 1.1f, 'a' } } } } } } },
              { 2,
                { { 2.2f,
                    { { 'b', { T{ 2, 2.2f, 'b' } } },
                      { 'c', { T{ 2, 2.2f, 'c' } } } } } } },
              { 3,
                { { 3.3f,
                    { { 'd',
                          { T{ 3, 3.3f, 'd' } } },
                      { 'e',
                          { T{ 3, 3.3f, 'e' } } },
                      { 'f',
                          { T{ 3, 3.3f, 'f' } } } } } } } } };

        assert(actual == expected);
    }
}

