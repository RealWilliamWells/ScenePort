#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace tbd {

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
};

};