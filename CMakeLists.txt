cmake_minimum_required(VERSION 3.5.0)
project(proj VERSION 0.1.0 LANGUAGES C CXX)

# Find Raylib
find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})


find_package(raylib REQUIRED)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_compile_options(-Wall)

add_executable(proj src/main.cpp src/TextEdit.cpp src/Action.cpp src/Dialog.cpp src/Config.cpp)
# Link Raylib 
target_link_libraries(proj PRIVATE raylib)
target_link_libraries(proj PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(proj PUBLIC ${CMAKE_SOURCE_DIR}/include)
