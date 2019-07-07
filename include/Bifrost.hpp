#pragma once
#include <array>
#include <cmath>
#include <unordered_map>
#include <vector>

template <class Key, class Value>
class Bifrost
{
public:
  Bifrost(const size_t numBuckets, const float cellSize);

  void Insert(const Key &aKey, Value &aValue);

  void Neighbors(const Key &aKey, std::vector<Value> &neighborList);

  void Clear() { mHashtable.clear(); }

private:
  struct DiscreteKey3D
  {
    DiscreteKey3D() { keys[0] = keys[1] = keys[2] = 0; }
    DiscreteKey3D(int i, int j, int k)
    {
      keys[0] = i;
      keys[1] = j;
      keys[2] = k;
    }
    int keys[3];
    int &operator[](int i) { return keys[i]; }
    const int &operator[](int i) const { return keys[i]; }
    bool operator==(const DiscreteKey3D &rhs) const
    {
      return this->keys[0] == rhs.keys[0] && this->keys[1] == rhs.keys[1] && this->keys[2] == rhs.keys[2];
    }

    DiscreteKey3D operator+(const DiscreteKey3D &rhs)
    {
      DiscreteKey3D sum;
      sum.keys[0] = this->keys[0] + rhs.keys[0];
      sum.keys[1] = this->keys[1] + rhs.keys[1];
      sum.keys[2] = this->keys[2] + rhs.keys[2];
      return sum;
    }
  };

  struct SpatialHash : std::unary_function<DiscreteKey3D, size_t>
  {
    size_t operator()(const DiscreteKey3D pos) const
    {
      const unsigned int prime1 = 73856093;
      const unsigned int prime2 = 19349663;
      const unsigned int prime3 = 83492791;
      return size_t((pos[0] * prime1) ^ (pos[1] * prime2) ^ (pos[2] * prime3));
    }
  };

  DiscreteKey3D Discretize(const Key &key) const
  {
    DiscreteKey3D dKey;
    dKey[0] = static_cast<int>(std::floor(key[0] * mInverseCellSize));
    dKey[1] = static_cast<int>(std::floor(key[1] * mInverseCellSize));
    dKey[2] = static_cast<int>(std::floor(key[2] * mInverseCellSize));
    return dKey;
  }

  typedef std::unordered_map<DiscreteKey3D, std::vector<Value>, SpatialHash> Hashtable;
  Hashtable mHashtable;
  const float mInverseCellSize;
  std::vector<DiscreteKey3D> mOffsets;
};

template <class Key, class Value>
Bifrost<Key, Value>::Bifrost(const size_t numBuckets, const float cellSize)
    : mHashtable(numBuckets), mInverseCellSize(1.f / cellSize)
{
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      for (int k = -1; k <= 1; k++)
        mOffsets.push_back(DiscreteKey3D(i, j, k));
}

template <class Key, class Value>
void Bifrost<Key, Value>::Insert(const Key &aKey, Value &aValue)
{
  mHashtable[Discretize(aKey)].push_back(aValue);
}

template <class Key, class Value>
void Bifrost<Key, Value>::Neighbors(const Key &aKey,
                                    std::vector<Value> &neighborList)
{
  auto dKey = Discretize(aKey);
  for (const auto &anOffset : mOffsets)
  {
    auto it = mHashtable.find(dKey + anOffset);
    if (it != mHashtable.end())
    {
      neighborList.insert(neighborList.end(), it->second.begin(),
                          it->second.end());
    }
  }
}
