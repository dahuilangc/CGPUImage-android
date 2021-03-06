/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESWIRLFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESWIRLFILTER_H


#include "GPUImageFilter.h"

class GPUImageSwirlFilter : public GPUImageFilter{
public:
    GPUImageSwirlFilter();
    virtual ~GPUImageSwirlFilter();

    void setCenter(float x, float y);

    void setRadius(float radius);
    void setRadius(int percent);
    void setAngle(float angle);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /// The center about which to apply the distortion, with a default of (0.5, 0.5)
    GLfloat m_pCenter[2];

    /// The radius of the distortion, ranging from 0.0 to 1.0, with a default of 0.5
    GLfloat m_fRadius;

    /// The amount of distortion to apply, with a minimum of 0.0 and a default of 1.0
    GLfloat m_fAngle;


    GLint m_iCenterUniformLocation;
    GLint m_iRadiusUniformLocation;
    GLint m_iAngleUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESWIRLFILTER_H
