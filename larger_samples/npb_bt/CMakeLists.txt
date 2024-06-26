cmake_minimum_required(VERSION 3.11)
project(perf_prog_npb_bt)

set_property(GLOBAL PROPERTY C_STANDARD 11)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wno-unknown-pragmas -Wno-unused-parameter)
endif()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.h)

link_libraries(m)

add_executable(npb_bt_w-o0 ${SOURCE_FILES})
target_include_directories(npb_bt_w-o0 PRIVATE src/w)
target_compile_options(npb_bt_w-o0 PRIVATE -O0)

add_executable(npb_bt_w-o1 ${SOURCE_FILES})
target_include_directories(npb_bt_w-o1 PRIVATE src/w)
target_compile_options(npb_bt_w-o1 PRIVATE -O1)

add_executable(npb_bt_w-o2 ${SOURCE_FILES})
target_include_directories(npb_bt_w-o2 PRIVATE src/w)
target_compile_options(npb_bt_w-o2 PRIVATE -O2)

add_executable(npb_bt_w-o3 ${SOURCE_FILES})
target_include_directories(npb_bt_w-o3 PRIVATE src/w)
target_compile_options(npb_bt_w-o3 PRIVATE -O3)

add_executable(npb_bt_w-os ${SOURCE_FILES})
target_include_directories(npb_bt_w-os PRIVATE src/w)
target_compile_options(npb_bt_w-os PRIVATE -Os)

add_executable(npb_bt_w-ofast ${SOURCE_FILES})
target_include_directories(npb_bt_w-ofast PRIVATE src/w)
target_compile_options(npb_bt_w-ofast PRIVATE -Ofast)


add_executable(npb_bt_s ${SOURCE_FILES})
target_include_directories(npb_bt_s PRIVATE src/s)

add_executable(npb_bt_a ${SOURCE_FILES})
target_include_directories(npb_bt_a PRIVATE src/a)

add_executable(npb_bt_b ${SOURCE_FILES})
target_include_directories(npb_bt_b PRIVATE src/b)

add_executable(npb_bt_c ${SOURCE_FILES})
target_include_directories(npb_bt_c PRIVATE src/c)
