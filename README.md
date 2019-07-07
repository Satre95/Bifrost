# Bifrost

Bifrost is a spatial hash table implementation that allows for _O(1)_ average insertion, lookup, and neigbhor query. As it is header-only, simply drop the Bifrost [header](include/Bifrost.hpp) into your project to get started.

## Requirements
  - A compiler with C++11 support.
  - That's it!

## Using Bifrost
Bifrost is implemented using a standard `Key`-`Value` storage symantic. The only constraint that Bifrost places on the use is that keys must support the `operator[]` overload, and must have 3 members indexed using that operator. Below is an example for an custom arbitrary type.

~~~
struct short3 {
    short data[3];
    short operator[](int idx) { return data[i]; }
};

struct SomeObjectType {
    int myMember;
    // Other member vars...
};

Bifrost<short3, SomeObjectType> bifrost;

short3 index;
SomeObjectType someObject;
//... Init your Key and Value
bifrost.Insert(index, someObject);
~~~

Bifrost is intended for use with 3D data, however, it can be easily be used for 2D indexes, simply set the 3rd element in your index to zero.