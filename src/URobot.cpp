// ur_robot.cpp
#include "URobot.hpp"
#include <stdexcept>

URobot::URobot(const std::string& robot_ip) : robot_ip(robot_ip) {}

URobot::~URobot() = default;

bool URobot::initialize() {
    try {
        rtde_control = std::make_unique<ur_rtde::RTDEControlInterface>(robot_ip);
        rtde_receive = std::make_unique<ur_rtde::RTDEReceiveInterface>(robot_ip);
        return true;
    } catch (const std::exception& e) {
        // Handle error
        return false;
    }
}

bool URobot::moveTo(const std::array<double, 6>& position) {
    try {
        std::vector<double> pos(position.begin(), position.end());
        return rtde_control->moveL(pos);
    } catch (const std::exception& e) {
        // Handle error
        return false;
    }
}

std::array<double, 6> URobot::getCurrentPosition() const {
    try {
        std::vector<double> pos = rtde_receive->getActualTCPPose();
        std::array<double, 6> position;
        std::copy_n(pos.begin(), 6, position.begin());
        return position;
    } catch (const std::exception& e) {
        // Handle error
        return {0, 0, 0, 0, 0, 0};
    }
}

double URobot::getCurrentSpeed() const {
    try {
        return rtde_receive->getActualTCPSpeed()[0]; // Assuming linear speed
    } catch (const std::exception& e) {
        // Handle error
        return 0.0;
    }
}

bool URobot::setSpeed(double speed) {
    try {
        return rtde_control->setTcpSpeed(speed);
    } catch (const std::exception& e) {
        // Handle error
        return false;
    }
}

bool URobot::startLinearMove(const std::array<double, 6>& endPosition) {
    try {
        std::vector<double> pos(endPosition.begin(), endPosition.end());
        return rtde_control->moveL(pos, 0.1, 0.1); // Adjust acceleration and speed as needed
    } catch (const std::exception& e) {
        // Handle error
        return false;
    }
}

bool URobot::stopMovement() {
    try {
        return rtde_control->stopRobot();
    } catch (const std::exception& e) {
        // Handle error
        return false;
    }
}