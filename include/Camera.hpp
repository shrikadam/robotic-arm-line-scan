// camera.hpp
#pragma once

#include <vector>
#include <cstdint>

class Camera {
public:
    virtual ~Camera() = default;

    // Initialize the camera
    virtual bool initialize() = 0;

    // Start the acquisition
    virtual bool startAcquisition() = 0;

    // Stop the acquisition
    virtual bool stopAcquisition() = 0;

    // Grab a single line
    virtual std::vector<uint8_t> grabLine() = 0;

    // Set exposure time
    virtual bool setExposureTime(double exposureTimeMs) = 0;

    // Get current frame rate
    virtual double getFrameRate() const = 0;
};
