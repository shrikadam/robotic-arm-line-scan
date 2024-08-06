// ur_robot.hpp
#pragma once

#include "Robot.hpp"
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

class URobot : public Robot {
public:
    URobot(const std::string& robot_ip);
    ~URobot() override;

    bool initialize() override;
    bool moveTo(const std::array<double, 6>& position) override;
    std::array<double, 6> getCurrentPosition() const override;
    double getCurrentSpeed() const override;
    bool setSpeed(double speed) override;
    bool startLinearMove(const std::array<double, 6>& endPosition) override;
    bool stopMovement() override;

private:
    std::unique_ptr<ur_rtde::RTDEControlInterface> rtde_control;
    std::unique_ptr<ur_rtde::RTDEReceiveInterface> rtde_receive;
    std::string robot_ip;
};