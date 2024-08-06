// pylon_camera.cpp
#include "PylonCamera.hpp"
#include <stdexcept>

PylonCamera::PylonCamera() {
    Pylon::PylonInitialize();
}

PylonCamera::~PylonCamera() {
    Pylon::PylonTerminate();
}

bool PylonCamera::initialize() {
    try {
        camera.Attach(Pylon::CTlFactory::GetInstance().CreateFirstDevice());
        camera.Open();
        return true;
    } catch (const Pylon::GenericException& e) {
        // Handle error
        return false;
    }
}

bool PylonCamera::startAcquisition() {
    try {
        camera.StartGrabbing(Pylon::GrabStrategy_OneByOne);
        return true;
    } catch (const Pylon::GenericException& e) {
        // Handle error
        return false;
    }
}

bool PylonCamera::stopAcquisition() {
    try {
        camera.StopGrabbing();
        return true;
    } catch (const Pylon::GenericException& e) {
        // Handle error
        return false;
    }
}

std::vector<uint8_t> PylonCamera::grabLine() {
    try {
        camera.RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
        
        if (ptrGrabResult->GrabSucceeded()) {
            const uint8_t* pImageBuffer = static_cast<uint8_t*>(ptrGrabResult->GetBuffer());
            return std::vector<uint8_t>(pImageBuffer, pImageBuffer + ptrGrabResult->GetWidth());
        } else {
            // Handle grab failure
            return std::vector<uint8_t>();
        }
    } catch (const Pylon::GenericException& e) {
        // Handle error
        return std::vector<uint8_t>();
    }
}

bool PylonCamera::setExposureTime(double exposureTimeMs) {
    try {
        camera.ExposureTime.SetValue(exposureTimeMs * 1000); // Convert ms to μs
        return true;
    } catch (const Pylon::GenericException& e) {
        // Handle error
        return false;
    }
}

double PylonCamera::getFrameRate() const {
    try {
        return camera.ResultingFrameRate.GetValue();
    } catch (const Pylon::GenericException& e) {
        // Handle error
        return 0.0;
    }
}
