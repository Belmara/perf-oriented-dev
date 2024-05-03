cmake_minimum_required(VERSION 3.10)
project(perf_oriented_prog_samples)

set_property(GLOBAL PROPERTY C_STANDARD 11)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(mmul mmul/mmul.c)

add_executable(mmul-o0 mmul/mmul.c)
target_compile_options(mmul-o0 PRIVATE -O0)

add_executable(mmul-o1 mmul/mmul.c)
target_compile_options(mmul-o1 PRIVATE -O1)

add_executable(mmul-o2 mmul/mmul.c)
target_compile_options(mmul-o2 PRIVATE -O2)

add_executable(mmul-o3 mmul/mmul.c)
target_compile_options(mmul-o3 PRIVATE -O3)

add_executable(mmul-os mmul/mmul.c)
target_compile_options(mmul-os PRIVATE -Os)

add_executable(mmul-ofast mmul/mmul.c)
target_compile_options(mmul-ofast PRIVATE -Ofast)



add_executable(delannoy delannoy/delannoy.c)

add_executable(delannoy-o0 delannoy/delannoy.c)
target_compile_options(delannoy-o0 PRIVATE -O0)

add_executable(delannoy-o1 delannoy/delannoy.c)
target_compile_options(delannoy-o1 PRIVATE -O1)

add_executable(delannoy-o2 delannoy/delannoy.c)
target_compile_options(delannoy-o2 PRIVATE -O2)

add_executable(delannoy-o3 delannoy/delannoy.c)
target_compile_options(delannoy-o3 PRIVATE -O3)

add_executable(delannoy-os delannoy/delannoy.c)
target_compile_options(delannoy-os PRIVATE -Os)

add_executable(delannoy-ofast delannoy/delannoy.c)
target_compile_options(delannoy-ofast PRIVATE -Ofast)


add_executable(qap qap/qap.c)

add_executable(qap-o0 qap/qap.c)
target_compile_options(qap-o0 PRIVATE -O0)

add_executable(qap-o1 qap/qap.c)
target_compile_options(qap-o1 PRIVATE -O1)

add_executable(qap-o2 qap/qap.c)
target_compile_options(qap-o2 PRIVATE -O2)

add_executable(qap-o3 qap/qap.c)
target_compile_options(qap-o3 PRIVATE -O3)

add_executable(qap-os qap/qap.c)
target_compile_options(qap-os PRIVATE -Os)

add_executable(qap-ofast qap/qap.c)
target_compile_options(qap-ofast PRIVATE -Ofast)






add_executable(nbody nbody/nbody.c)
target_link_libraries(nbody m)


add_executable(nbody-o0 nbody/nbody.c)
target_compile_options(nbody-o0 PRIVATE -O0)
target_link_libraries(nbody-o0 m)


add_executable(nbody-o1 nbody/nbody.c)
target_compile_options(nbody-o1 PRIVATE -O1)
target_link_libraries(nbody-o1 m)


add_executable(nbody-o2 nbody/nbody.c)
target_compile_options(nbody-o2 PRIVATE -O2)
target_link_libraries(nbody-o2 m)


add_executable(nbody-o3 nbody/nbody.c)
target_compile_options(nbody-o3 PRIVATE -O3)
target_link_libraries(nbody-o3 m)


add_executable(nbody-os nbody/nbody.c)
target_compile_options(nbody-os PRIVATE -Os)
target_link_libraries(nbody-os m)


add_executable(nbody-ofast nbody/nbody.c)
target_compile_options(nbody-ofast PRIVATE -Ofast)
target_link_libraries(nbody-ofast m)






# add_executable(filesearch filesearch/filesearch.c)

# add_executable(filegen filegen/filegen.c)
