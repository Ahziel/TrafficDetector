#include "processing/MotionDetector.h"

CMotionDetector::CMotionDetector()
{
	m_pImageUn = NULL;
	m_pImageDeux = NULL;
	m_pImageTrois = NULL;
	m_pImageUnDeux = NULL;
	m_pImageDeuxTrois = NULL;
	m_pImageResult = NULL;
}

void CMotionDetector::newImage(IplImage* p_pImage)
{
	this->bufferize(p_pImage);
	IplImage* img = this->calculus();
	if (img != NULL) emit calculusNewImage(img);
}

CMotionDetector ::~CMotionDetector()
{
}

void CMotionDetector::bufferize(IplImage* p_pImage) {
	IplImage* image_Gray;
	image_Gray = cvCreateImage(cvSize(p_pImage->width, p_pImage->height), IPL_DEPTH_8U, 1);
	cvCvtColor(p_pImage, image_Gray, CV_BGR2GRAY);

	//debut buffer tournant sur 3 images
	if (m_pImageUn == NULL) {
		m_pImageUn = cvCloneImage(image_Gray);
		return;
	}
	else if (m_pImageDeux == NULL) {
		m_pImageDeux = cvCloneImage(image_Gray);
		return;
	}
	else if (m_pImageTrois == NULL) {
		m_pImageTrois = cvCloneImage(image_Gray);
	}
	else {
		cvReleaseImage(&m_pImageUn);
		m_pImageUn = m_pImageDeux;
		m_pImageDeux = m_pImageTrois;
		m_pImageTrois = cvCloneImage(image_Gray);
	}
	cvReleaseImage(&image_Gray);
}

IplImage* CMotionDetector::calculus() {
	if (m_pImageTrois == NULL) return NULL;
	if (m_pImageUnDeux == NULL) m_pImageUnDeux = cvCloneImage(m_pImageUn);
	if (m_pImageDeuxTrois == NULL) m_pImageDeuxTrois = cvCloneImage(m_pImageUn);
	if (m_pImageResult == NULL) m_pImageResult = cvCloneImage(m_pImageUn);

	cvAbsDiff(m_pImageUn, m_pImageDeux, m_pImageUnDeux);
	cvAbsDiff(m_pImageDeux, m_pImageTrois, m_pImageDeuxTrois);
	cvAnd(m_pImageUnDeux, m_pImageDeuxTrois, m_pImageResult);
	cvThreshold(m_pImageResult, m_pImageResult, 50, 255, CV_THRESH_BINARY);
	cvDilate(m_pImageResult, m_pImageResult, 0, 4);
	emit calculusNewImage(m_pImageResult);
	return m_pImageResult;

}

