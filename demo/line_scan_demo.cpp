#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "PylonCamera.hpp"
#include "URobot.hpp"

enum class ScanMode {
    LINE_SCAN,
    AREA_SCAN
};

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <scan_mode> <robot_ip>" << std::endl;
    std::cout << "  scan_mode: 'line' for line scan, 'area' for area scan" << std::endl;
    std::cout << "  robot_ip: IP address of the UR robot" << std::endl;
}

void lineScanMode(PylonCamera& camera, URobot& robot) {
    std::cout << "Starting line scan mode..." << std::endl;

    // Set up robot movement
    std::array<double, 6> startPosition = {0.0, -0.5, 0.5, 0, 3.14, 0};  // Example position
    std::array<double, 6> endPosition = {0.5, -0.5, 0.5, 0, 3.14, 0};    // Example position

    robot.moveTo(startPosition);
    robot.setSpeed(0.1);  // 100 mm/s

    camera.startAcquisition();
    robot.startLinearMove(endPosition);

    // Simulate line acquisition
    for (int i = 0; i < 100; ++i) {  // Acquire 100 lines as an example
        std::vector<uint8_t> line = camera.grabLine();
        std::cout << "Acquired line " << i << ", size: " << line.size() << " pixels" << std::endl;
        
        // In a real application, you would process and store the line here
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simulate processing time
    }

    camera.stopAcquisition();
    robot.stopMovement();
}

void areaScanMode(PylonCamera& camera, URobot& robot) {
    std::cout << "Starting area scan mode..." << std::endl;

    // Set up robot positions for multiple shots
    std::vector<std::array<double, 6>> positions = {
        {0.0, -0.5, 0.5, 0, 3.14, 0},
        {0.1, -0.5, 0.5, 0, 3.14, 0},
        {0.2, -0.5, 0.5, 0, 3.14, 0},
        {0.3, -0.5, 0.5, 0, 3.14, 0},
        {0.4, -0.5, 0.5, 0, 3.14, 0}
    };

    camera.startAcquisition();

    for (const auto& position : positions) {
        robot.moveTo(position);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Wait for robot to settle

        // In area scan mode, we'll use grabLine() multiple times to simulate grabbing a full image
        std::vector<std::vector<uint8_t>> image;
        for (int i = 0; i < 480; ++i) {  // Simulate 480 lines for a full image
            std::vector<uint8_t> line = camera.grabLine();
            image.push_back(line);
        }

        std::cout << "Acquired image at position "
                  << position[0] << ", " << position[1] << ", " << position[2]
                  << ", size: " << image.size() << " x " << image[0].size() << " pixels" << std::endl;

        // In a real application, you would process and store the image here
    }

    camera.stopAcquisition();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    std::string modeArg = argv[1];
    std::string robotIp = argv[2];

    ScanMode mode;
    if (modeArg == "line") {
        mode = ScanMode::LINE_SCAN;
    } else if (modeArg == "area") {
        mode = ScanMode::AREA_SCAN;
    } else {
        std::cerr << "Invalid scan mode. Use 'line' or 'area'." << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    try {
        PylonCamera camera;
        URobot robot(robotIp);

        if (!camera.initialize()) {
            std::cerr << "Failed to initialize camera" << std::endl;
            return 1;
        }

        if (!robot.initialize()) {
            std::cerr << "Failed to initialize robot" << std::endl;
            return 1;
        }

        switch (mode) {
            case ScanMode::LINE_SCAN:
                lineScanMode(camera, robot);
                break;
            case ScanMode::AREA_SCAN:
                areaScanMode(camera, robot);
                break;
        }

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
