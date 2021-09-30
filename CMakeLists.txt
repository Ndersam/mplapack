cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)

add_subdirectory(mplapack/reference)
add_subdirectory(mpblas/optimized)
add_subdirectory(mpblas/reference)

add_library(lapack SHARED
	$<TARGET_OBJECTS:mplapack>
	$<TARGET_OBJECTS:mpblas_reference>
	#$<TARGET_OBJECTS:mpblas_optimized>
)

