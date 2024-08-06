// pylon_camera.hpp
#pragma once

#include "Camera.hpp"
#include <pylon/PylonIncludes.h>

class PylonCamera : public Camera {
public:
    PylonCamera();
    ~PylonCamera() override;

    bool initialize() override;
    bool startAcquisition() override;
    bool stopAcquisition() override;
    std::vector<uint8_t> grabLine() override;
    bool setExposureTime(double exposureTimeMs) override;
    double getFrameRate() const override;

private:
    Pylon::CInstantCamera camera;
    Pylon::CGrabResultPtr ptrGrabResult;
};