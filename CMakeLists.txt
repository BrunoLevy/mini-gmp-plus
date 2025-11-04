cmake_minimum_required(VERSION 3.5...3.30)
project(mini-gmp-plus)

add_library(mini-gmp-plus SHARED mini-gmp.c mini-mpq.c)
set_target_properties(mini-gmp-plus PROPERTIES VERSION 6.2)
set_target_properties(mini-gmp-plus PROPERTIES SOVERSION 6.2)

if(MINI_GMP_PLUS_WITH_TESTS)
   add_subdirectory(tests)
endif()
