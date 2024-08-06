// dalsa_camera.hpp
#pragma once

#include "Camera.hpp"
#include <memory>
#include <SapClassBasic.h>

class DalsaCamera : public Camera {
public:
    DalsaCamera();
    ~DalsaCamera() override;

    bool initialize() override;
    bool startAcquisition() override;
    bool stopAcquisition() override;
    std::vector<uint8_t> grabLine() override;
    bool setExposureTime(double exposureTimeMs) override;
    double getFrameRate() const override;

private:
    std::unique_ptr<SapAcquisition> m_Acquisition;
    std::unique_ptr<SapBuffer> m_Buffer;
    std::unique_ptr<SapTransfer> m_Transfer;

    SapAcqDevice* m_AcqDevice;
    BOOL m_IsInitialized;
    int m_Width;
    int m_Height;

    static void XferCallback(SapXferCallbackInfo* pInfo);
    void CreateResources();
    void DestroyResources();
};