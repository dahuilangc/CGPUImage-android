/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageRGBClosingFilter.h"


GPUImageRGBClosingFilter::GPUImageRGBClosingFilter()
    : GPUImageFilterGroup(),
      m_pErosionFilter(NULL),
      m_pDilationFilter(NULL)
{
    initWithRadius(1);
}

GPUImageRGBClosingFilter::GPUImageRGBClosingFilter(int radius)
    : GPUImageFilterGroup(),
      m_pErosionFilter(NULL),
      m_pDilationFilter(NULL)
{
    initWithRadius(radius);
}

GPUImageRGBClosingFilter::~GPUImageRGBClosingFilter()
{
    this->release();
}

bool GPUImageRGBClosingFilter::release()
{
    if(m_pErosionFilter){
        delete m_pErosionFilter;
        m_pErosionFilter = NULL;
    }

    if(m_pDilationFilter){
        delete m_pDilationFilter;
        m_pDilationFilter = NULL;
    }
    return true;
}

void GPUImageRGBClosingFilter::initWithRadius(int radius)
{
    m_pDilationFilter = new GPUImageRGBDilationFilter(radius);

    m_pErosionFilter = new GPUImageRGBErosionFilter(radius);

    addFilter(m_pDilationFilter);
    addFilter(m_pErosionFilter);
}

