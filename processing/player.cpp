#include "player.h"

Player::Player(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

bool Player::loadVideo(string filename) {

    capture  =  new cv::VideoCapture(filename);

    if (capture->isOpened())
    {
        originalFrameRate = (int) capture->get(CV_CAP_PROP_FPS);
        frameRate = originalFrameRate;
        return true;
    }
    else
        return false;
}

void Player::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void Player::run()
{
    while(!stop){
        if (!capture->read(frame))
        {
            stop = true;
        }
        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);
        }
        emit processedImage(img);
        emit sendFrameToProcess(&img);
        this->msleep((1000/frameRate));
    }
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    capture->release();
    delete capture;
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void Player::Stop()
{
    stop = true;
}
void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
bool Player::isStopped() const{
    return this->stop;
}

double Player::getCurrentFrame(){

    return capture->get(CV_CAP_PROP_POS_FRAMES);
}

double Player::getNumberOfFrames(){

    return capture->get(CV_CAP_PROP_FRAME_COUNT);
}

double Player::getFrameRate(){
    return frameRate;
}

double Player::getOriginalFrameRate()
{
    return originalFrameRate;
}

void Player::setCurrentFrame( int frameNumber )
{
    capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}

void Player::setFrameRate(int val)
{
    frameRate = val;
}
