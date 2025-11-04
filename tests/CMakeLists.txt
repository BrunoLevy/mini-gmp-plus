include(CTest)
enable_testing()

if(APPLE)
   add_include_directories("/opt/homebrew/include")
   add_link_directories("/opt/homebrew/lib")
endif()

add_library(mini-gmp-plus-test-lib OBJECT hex-random.c mini-random.c testutils.c)



set(MINI_GMP_TESTS
   t-add t-sub t-mul t-invert t-div t-div_2exp
   t-double t-cmp_d t-gcd t-lcm t-import t-comb t-signed
   t-sqrt t-root t-powm t-logops t-bitops t-scan t-str
   t-reuse t-aorsmul t-limbs t-cong t-pprime_p t-lucm
   t-mpq_addsub t-mpq_muldiv t-mpq_muldiv_2exp t-mpq_str
   t-mpq_double
)

foreach(T ${MINI_GMP_TESTS})
   add_executable(${T} ${T}.c)
   target_link_libraries(${T} mini-gmp-plus mini-gmp-plus-test-lib gmp m)
   add_test(NAME ${T} COMMAND ${T})
endforeach()
