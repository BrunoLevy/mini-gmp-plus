add_library(mini-gmp-plus SHARED mini-gmp.c mini-mpq.c)
set_target_properties(mini-gmp-plus PROPERTIES VERSION 6.2)
set_target_properties(mini-gmp-plus PROPERTIES SOVERSION 6.2)
