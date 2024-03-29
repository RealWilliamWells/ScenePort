#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#ifndef NO_CEREAL
#include "cereal/types/memory.hpp"
#include "cereal/archives/binary.hpp"
#endif

namespace sp {

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

// Using this to remove GLM dependency.
template<typename T>
struct Vector3 {
  T x, y, z;

#ifndef NO_CEREAL
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( x, y, z );
  }
#endif
};

};