#ifndef __CBACKGROUNDDETECTOR__
#define __CBACKGROUNDDETECTOR__

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <QtWidgets/QLabel>


class CBackgroundDetector : public QObject
{
	Q_OBJECT

public:
	struct GRAY { int g; };
	CBackgroundDetector();
	~CBackgroundDetector();

	void setPixelGrey(IplImage* img, int x, int y, GRAY gr) {
		((uchar *)(img->imageData + img->widthStep*y))[x] = gr.g;
	}

	GRAY getPixelGrey(IplImage* img, int x, int y) {
		GRAY gr;
		gr.g = ((uchar *)(img->imageData + img->widthStep*y))[x];
		return gr;
	}

	IplImage* calculus(IplImage* p_pImage, IplImage* p_pImageMask = NULL);

	
public slots:
	void newImage(IplImage*);
	void setGamma(float p_fGamma);

signals:
	void calculusNewImage(IplImage*);

private:
	IplImage* m_pImageRef;
	IplImage* m_pImage_Gray;
	float  m_fGamma;
};

#endif 
