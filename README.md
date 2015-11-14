## Copyright (C) 2014 Lukasz Czerwinski
  
## GroupBy
groupBy is a simple project. In fact this is just one function only. The function takes a container and groups its items by a given groupping function or functions.

##
Project webpage: https://github.com/wo3kie/groupBy

## Requirements
C++11  

## How to build it
make

## Tested with
clang++-3.5  
g++-4.9

## How to use it?
For a container with objects of type T

```{r, engine='cpp'}  
std::vector< T > v{ {
    T{ 1, 1.1f, 'a' },
    T{ 2, 2.2f, 'b' },
    T{ 2, 2.2f, 'c' },
    T{ 3, 3.3f, 'd' },
    T{ 3, 3.3f, 'e' },
    T{ 3, 3.3f, 'f' } } };
```

where T is defined as follow

```{r, engine='cpp'}  
struct T
{
    int i;
    float f;
    char c;
};
```

create a function

```{r, engine='cpp'}  
int get_i( T const & t )
{
    return t.i;
}
```

or functor

```{r, engine='cpp'}  
struct Get_i
{
    int operator(){ T const & t )
    {
        return t.i;
    }
};
```

or lambda which defines how would you like to group said objects. Pass it to groupBy function

```{r, engine='cpp'}  
std::map< int, std::vector< T > > const actual
    = groupBy( v.begin(), v.end(), & get_i );
```

or

```{r, engine='cpp'}  
std::map< int, std::vector< T > > const actual
    = groupBy( v.begin(), v.end(), Get_i() );
```
  
or
  
```{r, engine='cpp'}  
std::map< int, std::vector< T > > const actual
    = groupBy( v.begin(), v.end(), []( T const & t ){ return t.i; } );
```

As a result you get a std::map with objects being groupped

```{r, engine='cpp'}  
std::map< int, std::vector< T > > const expected {
  { { 1, { T{ 1, 1.1f, 'a' } } },
    { 2, { T{ 2, 2.2f, 'b' }, T{ 2, 2.2f, 'c' } } },
    { 3, { T{ 3, 3.3f, 'd' }, T{ 3, 3.3f, 'e' }, T{ 3, 3.3f, 'f' } } } }
};
```

If  

```{r, engine='cpp'}  
assert( actual != expected );
```

let me know !

You may pass as many grouping functions as you wish. For more complicated examples please take a look at main.cpp which contains unit tests.

