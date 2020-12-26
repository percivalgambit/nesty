#ifndef UTIL_STORAGE_UNIT_H_
#define UTIL_STORAGE_UNIT_H_

#include "util/strong_int.h"

#include <cstdint>

namespace util {

DEFINE_STRONG_INT_TYPE(ByteSize, uint64_t);

ByteSize Bytes(uint64_t b) { return ByteSize(b); }
ByteSize Kilobytes(uint64_t kb) { return Bytes(kb) * 1024; }
ByteSize Megabytes(uint64_t mb) { return Kilobytes(mb) * 1024; }
ByteSize Gigabytes(uint64_t gb) { return Megabytes(gb) * 1024; }
ByteSize Terabytes(uint64_t tb) { return Gigabytes(tb) * 1024; }

}  // namespace util

#endif  // UTIL_STORAGE_UNIT_H_
