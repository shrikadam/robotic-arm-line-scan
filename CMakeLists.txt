cmake_minimum_required(VERSION 3.12)
project(LineScanAcquisition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Pylon REQUIRED)
find_package(ur_rtde REQUIRED)

# Add your source files here
set(SOURCES
    src/PylonCamera.cpp
    src/URobot.cpp
    demo/line_scan_demo.cpp
)

# Add your header files here
set(HEADERS
    include/Camera.hpp
    include/Robot.hpp
    include/PylonCamera.hpp
    include/URobot.hpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
    ${Pylon_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Pylon_LIBRARIES}
    ur_rtde::rtde
)