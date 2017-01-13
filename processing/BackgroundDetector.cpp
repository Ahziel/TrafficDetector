#include "BackgroundDetector.h" 

CBackgroundDetector::CBackgroundDetector() : m_pImageRef(NULL), m_fGamma((float)0.9)
{
	m_pImage_Gray = NULL;
}

CBackgroundDetector::~CBackgroundDetector()
{
}

void CBackgroundDetector::newImage(IplImage* p_pImage)
{
	IplImage* img = this->calculus(p_pImage, NULL);
	emit calculusNewImage(img);
}

void CBackgroundDetector::setGamma(float p_fGamma)
{
	this->m_fGamma = p_fGamma;
}

IplImage* CBackgroundDetector::calculus(IplImage* p_pImage, IplImage* p_pImageMask) 
{

	if (m_pImage_Gray == NULL)
	{
		m_pImage_Gray = cvCreateImage(cvSize(p_pImage->width, p_pImage->height), IPL_DEPTH_8U, 1);
		
	}
	cvCvtColor(p_pImage, m_pImage_Gray, CV_BGR2GRAY);

	GRAY gr;
	if (m_pImageRef == NULL){
		m_pImageRef = cvCloneImage(m_pImage_Gray);
	}
	else {
		if (p_pImageMask == NULL) {
			for (int l = 0; l < m_pImageRef->width; ++l) {
				for (int j = 0; j < m_pImageRef->height; ++j) {
					gr.g = m_fGamma*getPixelGrey(m_pImageRef, l, j).g + (1 - m_fGamma)*getPixelGrey(m_pImage_Gray, l, j).g;
					setPixelGrey(m_pImageRef, l, j, gr);
				}
			}
		}
		else {
			for (int l = 0; l < m_pImageRef->width; ++l) {
				for (int j = 0; j < m_pImageRef->height; ++j) {
					if (getPixelGrey(p_pImageMask, l, j).g == 0) {
						gr.g = m_fGamma*getPixelGrey(m_pImageRef, l, j).g + (1 - m_fGamma)*getPixelGrey(m_pImage_Gray, l, j).g;
						setPixelGrey(m_pImageRef, l, j, gr);
					}
				}
			}
		}
	}
	return m_pImageRef;
}


