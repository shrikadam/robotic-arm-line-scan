// dalsa_camera.cpp
#include "DalsaCamera.hpp"
#include <stdexcept>
#include <iostream>

DalsaCamera::DalsaCamera()
    : m_AcqDevice(nullptr), m_IsInitialized(FALSE), m_Width(0), m_Height(0) {}

DalsaCamera::~DalsaCamera() {
    DestroyResources();
}

bool DalsaCamera::initialize() {
    if (m_IsInitialized) return true;

    try {
        CreateResources();
        m_IsInitialized = TRUE;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize Dalsa camera: " << e.what() << std::endl;
        return false;
    }
}

bool DalsaCamera::startAcquisition() {
    if (!m_IsInitialized) return false;

    m_Transfer->Grab();
    return true;
}

bool DalsaCamera::stopAcquisition() {
    if (!m_IsInitialized) return false;

    m_Transfer->Freeze();
    return true;
}

std::vector<uint8_t> DalsaCamera::grabLine() {
    if (!m_IsInitialized) return std::vector<uint8_t>();

    // Wait for the next buffer to be acquired
    m_Transfer->Wait(1000);

    // Get the raw buffer pointer
    void* pLine;
    m_Buffer->GetAddress(&pLine);

    // Copy the line data to a vector
    std::vector<uint8_t> lineData(m_Width);
    memcpy(lineData.data(), pLine, m_Width);

    return lineData;
}

bool DalsaCamera::setExposureTime(double exposureTimeMs) {
    if (!m_IsInitialized) return false;

    // Convert ms to µs
    int exposureTimeMicros = static_cast<int>(exposureTimeMs * 1000);
    
    // Set the exposure time
    return (m_AcqDevice->SetFeatureValue("ExposureTime", exposureTimeMicros) == TRUE);
}

double DalsaCamera::getFrameRate() const {
    if (!m_IsInitialized) return 0.0;

    int frameRate;
    if (m_AcqDevice->GetFeatureValue("AcquisitionFrameRate", &frameRate) == TRUE) {
        return static_cast<double>(frameRate);
    }
    return 0.0;
}

void DalsaCamera::XferCallback(SapXferCallbackInfo* pInfo) {
    // This callback is called when a new frame is acquired
    // You can add custom processing here if needed
}

void DalsaCamera::CreateResources() {
    // Create acquisition object
    m_Acquisition = std::make_unique<SapAcquisition>(SapLocation("Xtium-CL_MX4", 0), "");
    
    // Create buffer object
    m_Buffer = std::make_unique<SapBuffer>(1, m_Acquisition.get());

    // Create transfer object
    m_Transfer = std::make_unique<SapTransfer>(m_Acquisition.get(), m_Buffer.get(), XferCallback);

    // Get the acquisition device
    m_AcqDevice = m_Acquisition->GetAcqDevice();

    // Create all objects
    if (m_Acquisition->Create() && m_Buffer->Create() && m_Transfer->Create()) {
        // Get image dimensions
        m_Width = m_Buffer->GetWidth();
        m_Height = m_Buffer->GetHeight();
    } else {
        throw std::runtime_error("Failed to create Sapera resources");
    }
}

void DalsaCamera::DestroyResources() {
    if (m_Transfer) m_Transfer->Destroy();
    if (m_Buffer) m_Buffer->Destroy();
    if (m_Acquisition) m_Acquisition->Destroy();
    m_IsInitialized = FALSE;
}