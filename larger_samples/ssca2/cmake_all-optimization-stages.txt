cmake_minimum_required(VERSION 3.11)
project(perf_prog_npb_bt)

set_property(GLOBAL PROPERTY C_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.h src/sprng2.0/*.c src/sprng2.0/*.h)
include_directories(src/sprng2.0/include)

link_libraries(m)
add_definitions(-DLittleEndian, -DAdd__)

add_executable(ssca2-o0 ${SOURCE_FILES})
target_compile_options(ssca2-o0 PRIVATE -O0)

add_executable(ssca2-o1 ${SOURCE_FILES})
target_compile_options(ssca2-o1 PRIVATE -O1)

add_executable(ssca2-o2 ${SOURCE_FILES})
target_compile_options(ssca2-o2 PRIVATE -O2)

add_executable(ssca2-o3 ${SOURCE_FILES})
target_compile_options(ssca2-o3 PRIVATE -O3)

add_executable(ssca2-os ${SOURCE_FILES})
target_compile_options(ssca2-os PRIVATE -Os)

add_executable(ssca2-ofast ${SOURCE_FILES})
target_compile_options(ssca2-ofast PRIVATE -Ofast)      





