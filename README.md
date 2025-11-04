# mini-gmp-plus

This is a fork of the mini version of the
[GNU Multi-Precision library](https://gmplib.org/)
with some patches/optimizations for usage in numerical geometry (my changes
indicated with a [Bruno] tag).

This is work in progress.

As compared to mini-gmp, mini-gmp-plus has the following differences:
- limb size is fixed as 64 bits
- numbers smaller than a certain size (5 limbs) are stored in the mpz structure
- the file bitops64.h, not part of mini-gmp, contains some wrappers for
  efficient bit operations on 64-bit numbers, for GCC, Clang and
  VisualC++ using these compiler's intrinsics
- mini-gmp-plus is compiled as a dynamic library
- CMakeList optionally builds and run non-regression tests using CTest
