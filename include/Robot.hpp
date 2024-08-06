// robot.hpp
#pragma once

#include <array>

class Robot {
public:
    virtual ~Robot() = default;

    // Initialize the robot
    virtual bool initialize() = 0;

    // Move to a specific position
    virtual bool moveTo(const std::array<double, 6>& position) = 0;

    // Get current TCP position
    virtual std::array<double, 6> getCurrentPosition() const = 0;

    // Get current TCP speed
    virtual double getCurrentSpeed() const = 0;

    // Set TCP speed
    virtual bool setSpeed(double speed) = 0;

    // Start linear movement
    virtual bool startLinearMove(const std::array<double, 6>& endPosition) = 0;

    // Stop movement
    virtual bool stopMovement() = 0;
};