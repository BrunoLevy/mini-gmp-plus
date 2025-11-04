# A CMakeFile for mini-gmp test programs
# Bruno Levy, November 2025

include(CTest)
enable_testing()

#if(WIN32)
#   set(PKG_CONFIG_EXECUTABLE "D:\\a\\mini-gmp-plus\\mini-gmp-plus\\vcpkg\\installed\\x64-windows\\tools\\pkgconf\\pkgconf.exe")
#endif()

if(WIN32)
#  did not manage to make it work the clean way under Windows, so I'm
#  getting the include files and libs where they are...
   set(VCPKG_ROOT ${CMAKE_SOURCE_DIR}/../vcpkg)
   include_directories(${VCPKG_ROOT}/installed/x64-windows/include)
   link_directories(${VCPKG_ROOT}/installed/x64-windows/lib)
else()
#   for PkgConfig and gmp to work (see .github/Workflows/build.yml)
#   under MacOS: brew install pkgconf
#   under Windows:
#      git clone https://github.com/Microsoft/vcpkg --depth=1
#      cd vcpkg; cmd /c bootstrap-vcpkg.bat
#      vcpkg install pkgconf
#      vcpkg install gmp
   find_package(PkgConfig REQUIRED)
   pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)
   include_directories(${gmp_INCLUDE_DIRS})
endif


# These three files are systematically used by each test, made it an object lib

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
if(WIN32)
   target_link_libraries(${T} mini-gmp-plus mini-gmp-plus-test-lib gmp m)
else()
   target_link_libraries(
       ${T} mini-gmp-plus mini-gmp-plus-test-lib PkgConfig::gmp m
   )
endif()
   add_test(NAME ${T} COMMAND ${T})
endforeach()
