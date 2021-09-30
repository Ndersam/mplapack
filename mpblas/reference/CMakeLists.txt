add_library(mpblas_reference OBJECT)

add_compile_definitions(___MPLAPACK_BUILD_WITH_DOUBLE___)
add_compile_definitions(_USE_MATH_DEFINES)

file(GLOB_RECURSE SRCS *.cpp)

target_sources(mpblas_reference PRIVATE ${SRCS})