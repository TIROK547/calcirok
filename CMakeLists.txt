cmake_minimum_required(VERSION 3.20)
project(calcirok CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/boot.cpp
    src/main.cpp
    src/io.cpp
    src/input.cpp
    src/util.cpp
    src/platform.cpp
)

add_executable(calcirok ${SOURCES})

target_include_directories(calcirok PRIVATE include)

target_compile_options(calcirok PRIVATE
    -m32                    # 32-bit ELF — required by QEMU -kernel + Multiboot1
    -ffreestanding
    -fno-exceptions
    -fno-rtti
    -fno-stack-protector
    -fno-pie
    -nostdlib
    -Wall
    -Wextra
)

target_link_options(calcirok PRIVATE
    -m32
    -nostdlib
    -static
    -no-pie
    -T${CMAKE_SOURCE_DIR}/linker.ld
)
