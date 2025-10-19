/*
 * Bruno Levy October 2025
 * Some wrappers for bit operations on 64-bits integers, for different compilers
 *   GCC
 *   CLANG
 *   Visual C++
 */

#ifndef BITOPS64
#define BITOPS64

#include <stdint.h>
#include <assert.h>

#if defined(__GNUC__)
#define BITOPS64_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(_BitScanForward)
#pragma intrinsic(_BitScanBackward)
#pragma intrinsic(_shiftleft128)
#define BITOPS64_INLINE __forceinline
#endif


#if defined(__GNUC__)

/******************* GCC/CLANG **********************/

/**
 * \brief Counts the number of leading zeroes in a non-zero 64 bits integer
 * \pre x != 0
 * \param[in] x a 64 bits integer
 * \return the number of leading zeroes in \p x
 */
BITOPS64_INLINE int bitops64_clz_nonzero(uint64_t x) {
    assert(x != 0);
    return __builtin_clzll(x);
}

/**
 * \brief Counts the number of leading zeroes in a 64 bits integer
 * \details \p x can be zero (then it returns 64)
 * \param[in] x a 64 bits integer
 * \return the number of leading zeroes in \p x
 */
BITOPS64_INLINE int bitops64_clz(uint64_t x) {
    return (x == 0) ? 64 : __builtin_clzll(x);
}

/**
 * \brief Counts the number of trailing zeroes in a non-zero 64 bits integer
 * \pre x != 0
 * \param[in] x a 64 bits integer
 * \return the number of trailing zeroes in \p x
 */
BITOPS64_INLINE int bitops64_ctz_nonzero(uint64_t x) {
    assert(x != 0);
    return __builtin_ctzll(x);
}

/**
 * \brief Counts the number of trailing zeroes in a 64 bits integer
 * \details \p x can be zero (then it returns 64)
 * \param[in] x a 64 bits integer
 * \return the number of trailing zeroes in \p x
 */
BITOPS64_INLINE int bitops64_ctz(uint64_t x) {
    return (x == 0) ? 64 : __builtin_ctzll(x);
}

#pragma GCC diagnostic push // it's not ISO C++, but it's fine !
#pragma GCC diagnostic ignored "-Wpedantic"
typedef unsigned __int128 bitops64_uint128_t;
#pragma GCC diagnostic pop

/**
 * \brief Shifts a 128 bits integer to the left
 * \param[in] high , low the most significant and least significant
 *  limbs forming the 128-bits integer to shift
 * \param[in] shift the shift, in [0,64[
 * \return the most significant limb of (high:low) << shift
 */
BITOPS64_INLINE uint64_t bitops64_lshift128(
    uint64_t high, uint64_t low, int shift
) {
    assert(shift >= 0 && shift < 64);
    return (uint64_t)(
	(((bitops64_uint128_t)(high) << 64 |
	  (bitops64_uint128_t)(low)) << shift) >> 64
    );
}


/********************* Visual C++ *****************************/

#elif defined(_MSC_VER)

/**
 * \brief Counts the number of leading zeroes in a non-zero 64 bits integer
 * \pre x != 0
 * \param[in] x a 64 bits integer
 * \return the number of leading zeroes in \p x
 */
BITOPS64_INLINE int bitops64_clz_nonzero(uint64_t x) {
    assert(x != 0);
    unsigned long index;
    _BitScanBackward64(&index, x);
    return (int)index;
}

/**
 * \brief Counts the number of leading zeroes in a 64 bits integer
 * \details \p x can be zero (then it returns 64)
 * \param[in] x a 64 bits integer
 * \return the number of leading zeroes in \p x
 */
BITOPS64_INLINE int bitops64_clz(uint64_t x) {
    unsigned long index;
    return _BitScanBackward64(&index, x) ? (int)index : 64;
}

/**
 * \brief Counts the number of trailing zeroes in a non-zero 64 bits integer
 * \pre x != 0
 * \param[in] x a 64 bits integer
 * \return the number of trailing zeroes in \p x
 */
BITOPS64_INLINE int bitops64_ctz_nonzero(uint64_t x) {
    assert(x != 0);
    unsigned long index;
    _BitScanForward64(&index, x);
    return (int)index;
}

/**
 * \brief Counts the number of trailing zeroes in a 64 bits integer
 * \details \p x can be zero (then it returns 64)
 * \param[in] x a 64 bits integer
 * \return the number of trailing zeroes in \p x
 */
BITOPS64_INLINE int bitops64_ctz(uint64_t x) {
    unsigned long index;
    return _BitScanForward64(&index, x) ? (int)index : 64;
}

/**
 * \brief Shifts a 128 bits integer to the left
 * \param[in] high , low the most significant and least significant
 *  limbs forming the 128-bits integer to shift
 * \param[in] shift the shift, in [0,64[
 * \return the most significant limb of (high:low) << shift
 */
BITOPS64_INLINE uint64_t bitops64_lshift128(
    uint64_t high, uint64_t low, int shift
) {
    return shiftleft128(low, high, (char)shift);
}

#else
#error Compiler is unsupported

/**
 * \brief Shifts a 128 bits integer to the left
 * \param[in] high , low the most significant and least significant
 *  limbs forming the 128-bits integer to shift
 * \param[in] shift the shift, in [0,64[
 * \return the most significant limb of (high:low) << shift
 */
inline uint64_t bitops64_lshift128(uint64_t high, uint64_t low, int shift) {
    return (shift == 0) ? // shifting by 64 bits is UB
	high : ((high << shift) | (low >> (64 - shift)));
}


#endif

#endif
