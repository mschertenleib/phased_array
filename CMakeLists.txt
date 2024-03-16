cmake_minimum_required(VERSION 3.24)

project(phased_array LANGUAGES CXX)


include(cmake/CPM.cmake)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(OpenGL REQUIRED)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
CPMAddPackage(
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.8
)


CPMAddPackage(
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG v1.90.3
        DOWNLOAD_ONLY YES
)
add_library(imgui STATIC)
target_sources(imgui PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui.h
        ${imgui_SOURCE_DIR}/imgui_internal.h
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui SYSTEM
        PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PRIVATE OpenGL::GL glfw)


add_executable(phased_array)
target_compile_features(phased_array PRIVATE cxx_std_20)
target_sources(phased_array PRIVATE src/main.cpp)
target_link_libraries(phased_array PRIVATE
        OpenGL::GL
        glfw
        imgui
)


set(CLANG_WARNINGS
        -Wfatal-errors
        -Wall
        -Wextra
        -Wshadow
        -Wnon-virtual-dtor
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
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
        -Wuseless-cast
)
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(phased_array PRIVATE ${CLANG_WARNINGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(phased_array PRIVATE ${GCC_WARNINGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(phased_array PRIVATE /W4)
else ()
    message(WARNING "No warnings set for compiler '${CMAKE_CXX_COMPILER_ID}'")
endif ()


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

