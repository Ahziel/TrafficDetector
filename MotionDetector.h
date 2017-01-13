#ifndef __MOTIONDETECTOR__
#define __MOTIONDETECTOR__

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <QtWidgets/QLabel>

class CMotionDetector : public QObject
{
	Q_OBJECT
public:
	CMotionDetector();
	~CMotionDetector();

	void bufferize(IplImage* p_pImage);

	IplImage* calculus();

public slots:
	void newImage(IplImage*);

signals:
	void calculusNewImage(IplImage*);

private:
	IplImage* m_pImageUn;
	IplImage* m_pImageDeux;
	IplImage* m_pImageTrois;
	IplImage* m_pImageUnDeux;
	IplImage* m_pImageDeuxTrois;
	IplImage* m_pImageResult;
};

#endif
