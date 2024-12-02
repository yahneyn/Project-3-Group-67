cmake_minimum_required(VERSION 3.27.8)
project(Project_3_Group_67)

set(CMAKE_CXX_STANDARD 14)

# Include your bridges directory
include_directories(${PROJECT_SOURCE_DIR}/bridges/include)

# Attempt to find CURL
find_package(CURL REQUIRED)



# Add your executable
add_executable(Project_3_Group_67
        main.cpp
        Project3.h
)

# If CURL is found, add include directories and link libraries
if (CURL_FOUND)
    # Use target-specific commands to add include directories and link libraries
    target_include_directories(Project_3_Group_67 PRIVATE ${CURL_INCLUDE_DIRS})
    target_link_libraries(Project_3_Group_67 PRIVATE ${CURL_LIBRARIES})
else()
    message(FATAL_ERROR "CURL not found! Please install CURL or set the appropriate paths.")
endif()
