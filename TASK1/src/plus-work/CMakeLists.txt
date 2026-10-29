cmake_minimum_required(VERSION 3.8)
project(plus_work) 

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(ament_index_cpp REQUIRED)


add_executable(plus_work src/plus.cpp)

target_link_libraries(plus_work 
  yaml-cpp
  ament_index_cpp::ament_index_cpp
)
install(TARGETS plus_work
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()