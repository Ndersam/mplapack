add_library(mpblas_optimized OBJECT)

add_compile_definitions(___MPLAPACK_BUILD_WITH_DOUBLE___)
add_compile_definitions(_USE_MATH_DEFINES)

file(GLOB_RECURSE SRCS double/*.cpp)

target_sources(mpblas_optimized PRIVATE ${SRCS})