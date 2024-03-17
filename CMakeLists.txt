cmake_minimum_required(VERSION 3.11)
project(phased_array LANGUAGES C)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
        include(FetchContent)
        FetchContent_Declare(
                raylib
                DOWNLOAD_EXTRACT_TIMESTAMP OFF
                URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        )
        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED)
                set(FETCHCONTENT_QUIET NO)
                FetchContent_Populate(raylib)
                set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
                add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()
endif()


add_executable(phased_array src/main.c)
target_compile_features(phased_array PRIVATE c_std_99)
target_link_libraries(phased_array raylib)


set(CLANG_WARNINGS
        -Wfatal-errors
        -Wall
        -Wextra
        -Wshadow
        -Wcast-align
        -Wunused
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
)
set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
)
if (CMAKE_C_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(phased_array PRIVATE ${CLANG_WARNINGS})
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(phased_array PRIVATE ${GCC_WARNINGS})
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(phased_array PRIVATE /W4)
else ()
    message(WARNING "No warnings set for compiler '${CMAKE_C_COMPILER_ID}'")
endif ()


if (${PLATFORM} STREQUAL "Web")
    set_target_properties(phased_array PROPERTIES SUFFIX ".html")
endif()


if (APPLE)
    target_link_libraries(phased_array "-framework IOKit")
    target_link_libraries(phased_array "-framework Cocoa")
    target_link_libraries(phased_array "-framework OpenGL")
endif()


message(CHECK_START "Checking for IPO support")
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported_result OUTPUT ipo_supported_output)
if (ipo_supported_result)
    message(CHECK_PASS "supported")
    set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION_MIN_SIZE_REL TRUE)
else ()
    message(CHECK_FAIL "not supported")
endif ()

