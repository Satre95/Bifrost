# Bifrost

Bifrost is a spatial hash table implementation that allows for _O(1)_ average insertion, lookup, and neigbhor query. As it is header-only, simply drop the Bifrost [header](include/Bifrost.hpp) into your project to get started.

## Requirements
  - A compiler with C++11 support.
  - That's it!

## Using Bifrost
Bifrost is implemented using a standard `Key`-`Value` storage symantic. The only constraint that Bifrost places on the developer is that keys must support the `operator[]` overload, and must have 3 members indexed using that operator. Below is an example for a custom type.

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
//...Init your Key and Value

bifrost.Insert(index, someObject);
//...More insertions

std::vector<SomeObjectType> neighbors;
bifrost.Neighbors(index, neighbors);
for(auto & aNeighbor: neighbors) {
    //...Do something with the neighbors.
}
~~~

Bifrost is intended for use with 3D data, however, it can be easily be used for 2D indexes, simply set the 3rd element in your index to zero.

**Note:** When performing neighbor search, if there is a value matching the index being queried, it will be included in the returned list.

## Why Bifrost?
In the Marvel universe, the Bifrost is a device that Thor and other Asgardians use to to travel nearly instantaneously between locations in the universe. The time taken to travel between any two locations is always the same and is not affected by the size of the universe or the location being travelled to...