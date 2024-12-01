cmake_minimum_required(VERSION 3.27.8)
project(Project_3_Group_67)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/bridges/include)

find_package(CURL REQUIRED)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
endif()

add_executable(Project_3_Group_67
        main.cpp
        Project3.h
)

if (CURL_FOUND)
    target_link_libraries(Project_3_Group_67 ${CURL_LIBRARIES})
endif()
