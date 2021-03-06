/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLuminanceRangeFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _luminanceRange_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform lowp float rangeReduction;\n"
"\n"
"// Values from \"Graphics Shaders: Theory and Practice\" by Bailey and Cunningham\n"
"const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    mediump float luminance = dot(textureColor.rgb, luminanceWeighting);\n"
"    mediump float luminanceRatio = ((0.5 - luminance) * rangeReduction);\n"
"\n"
"    gl_FragColor = vec4((textureColor.rgb) + (luminanceRatio), textureColor.w);\n"
"}"
;

#else

// 片元着色器
extern const char _luminanceRange_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float rangeReduction;\n"
"\n"
"// Values from \"Graphics Shaders: Theory and Practice\" by Bailey and Cunningham\n"
"const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    float luminance = dot(textureColor.rgb, luminanceWeighting);\n"
"    float luminanceRatio = ((0.5 - luminance) * rangeReduction);\n"
"\n"
"    gl_FragColor = vec4((textureColor.rgb) + (luminanceRatio), textureColor.w);\n"
"}"
;

#endif




GPUImageLuminanceRangeFilter::GPUImageLuminanceRangeFilter()
    : GPUImageFilter(_luminanceRange_fragment_shader)
{
    m_fRangeReductionFactor = 0.6f;
    m_iRangeReductionFactorUniformLocation = -1;
}

GPUImageLuminanceRangeFilter::~GPUImageLuminanceRangeFilter()
{

}

void GPUImageLuminanceRangeFilter::setRangeReductionFactor(float rangeReductionFactor)
{
    m_fRangeReductionFactor = rangeReductionFactor;
}

void GPUImageLuminanceRangeFilter::setRangeReductionFactor(int percent)
{
    float max = 1.0f;
    float min = 0.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setRangeReductionFactor(value);
}

bool GPUImageLuminanceRangeFilter::createProgramExtra()
{
    m_iRangeReductionFactorUniformLocation = glGetUniformLocation(m_uProgram, "rangeReduction");
    return true;
}

bool GPUImageLuminanceRangeFilter::beforeDrawExtra()
{
    glUniform1f(m_iRangeReductionFactorUniformLocation, m_fRangeReductionFactor);
    return true;
}

