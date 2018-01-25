cmake_minimum_required(VERSION 2.8)

project(NBody)
add_executable(${PROJECT_NAME} "main.cpp")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
else()
    message("\n SFML not found")
endif()

#find_package(OpenMP)
#if (OPENMP_FOUND)
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

target_compile_options(${PROJECT_NAME}
  PRIVATE
#    -flto
    -march=native
    -std=c++17
    -O3
    -g3
    -m64
    -Werror
    -Wfatal-errors
    -pedantic-errors
    -Wall
    -Wextra
#    -floop-parallelize-all
#    -ftree-parallelize-loops=4
)
