# mini-gmp-plus

This is a fork of the mini version of the
[GNU Multi-Precision library](https://gmplib.org/)
with some patches/optimizations for usage in numerical geometry
and easy-to-use CMakeList (tested under Windows, Linux, Mac).

My changes are listed in [mini-gmp-plus-Changelog](mini-gmp-plus-Changelog),
and indicated by [Bruno Levy] tags in the sources.

Design rationale
----------------
In numerical geometry, one manipulates numbers that are relatively
small (a few 64-bit limbs), so Karatsuba multiplication is not
needed. On the other hand, it is interesting to avoid dynamic
allocation, hence numbers smaller than a certain threshold (that
corresponds to 5 64-bits numbers by default) are allocated on the
stack.

Features and specificities
--------------------------
As compared to `mini-gmp`, `mini-gmp-plus` has the following differences:
- _limitation_: limb size is fixed as 64 bits
- numbers smaller than a certain size (5 limbs) are stored in the `mpz_t`
  structure for better multithreading (avoids most dynamic allocations)
- the file [bitops64.h](bitops64.h), not part of mini-gmp, contains some
  wrappers for efficient bit operations on 64-bit numbers, for GCC, Clang and
  VisualC++ using these compiler's intrinsics
- `mini-gmp-plus` is compiled as a dynamic library
- [CMakeList.txt](CMakeList.txt) optionally builds and runs non-regression
  tests using CTest, use `cmake -D-DMINI_GMP_PLUS_WITH_TESTS=1` to compile and
  run the testsuite.
- The github action builds and runs the testsuite systematically. Under Windows,
  the github action installs gmp (through `vcpkg`) and declares it
  (through `pkgconf`) so that [tests/CMakeLists.txt](tests/CMakeLists.txt)
  sees it. Note that `gmp` is only needed if you want to run the non-regression
  testsuite.
