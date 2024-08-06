# Line Scan Acquisition System

## Overview

This project implements a flexible line scan acquisition system using a camera mounted on a robotic arm. It supports both line scan and area scan modes, allowing for versatile image acquisition in various industrial applications such as quality control, 3D reconstruction, and surface inspection.

## Features

- Supports both line scan and area scan modes
- Flexible camera interface using Basler's Pylon SDK
- Robot control using Universal Robots' RTDE interface
- Synchronized movement and image acquisition
- Easily extensible for different camera and robot models

## Prerequisites

- C++17 compatible compiler
- CMake (version 3.12 or higher)
- Basler Pylon SDK
- Universal Robots RTDE library
- A compatible Basler camera
- A Universal Robots arm (tested with UR5e, but should work with other models)

## Building the Project

1. Clone the repository:
git clone https://github.com/yourusername/line-scan-acquisition.git
cd line-scan-acquisition
2. Create a build directory:
mkdir build && cd build
3. Run CMake:
cmake ..
4. Build the project:
cmake --build .

## Usage
After building, you can run the program with the following command:
./LineScanAcquisition <scan_mode> <robot_ip>
Where:
- `<scan_mode>` is either `line` for line scan mode or `area` for area scan mode
- `<robot_ip>` is the IP address of your Universal Robots arm

Example:
./LineScanAcquisition line 192.168.1.100

## Project Structure

- `include/`: Header files
  - `Camera.hpp`: Abstract camera interface
  - `Robot.hpp`: Abstract robot interface
  - `PylonCamera.hpp`: Concrete implementation for Basler cameras
  - `URobot.hpp`: Concrete implementation for UR robots
- `src/`: Source files
  - `line_scan_demo.cpp`: Entry point and demo implementation
  - `PylonCamera.cpp`: Implementation of Pylon camera class
  - `URobot.cpp`: Implementation of UR robot class
- `CMakeLists.txt`: CMake build configuration

## Extending the Project

### Adding Support for a New Camera

1. Create a new class that inherits from the `Camera` interface.
2. Implement all the pure virtual functions defined in `Camera.hpp`.
3. Update the `CMakeLists.txt` to include any necessary libraries for the new camera.

### Adding Support for a New Robot

1. Create a new class that inherits from the `Robot` interface.
2. Implement all the pure virtual functions defined in `Robot.hpp`.
3. Update the `CMakeLists.txt` to include any necessary libraries for the new robot.

## Configuration

The current implementation uses hardcoded values for demonstration purposes. For a production environment, consider:

1. Implementing a configuration file system (e.g., JSON, YAML) to store parameters such as:
   - Camera settings (exposure time, frame rate)
   - Robot movement parameters (speed, acceleration)
   - Scan patterns and positions

2. Adding command-line options for more flexible runtime configuration.

## Future Improvements

- Implement a graphical user interface for easier operation
- Add real-time visualization of acquired data
- Implement more sophisticated error handling and logging
- Add unit tests and integration tests
- Implement a plugin system for easier extension with new cameras and robots

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Basler for the Pylon SDK
- Universal Robots for the RTDE interface
- All contributors and users of this project