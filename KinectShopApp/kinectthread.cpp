#include "kinectthread.h"

KinectThread::KinectThread(QObject* parent) :
QThread(parent),
continueProcessing(false),
m_hNextColorFrameEvent(NULL),
m_pVideoStreamHandle(NULL)
{

}


//--
KinectThread::~KinectThread()
{

}


//--
void
KinectThread::run()
{
    const int numEvents = 1;
    HANDLE hEvents[numEvents] = {m_hNextColorFrameEvent};

    continueProcessing = true;
    int nEventIdx;

    while ( continueProcessing )
    {

        // [rad] Wait for events, (not necessarily all) and time out is 100 msec.
        nEventIdx = WaitForMultipleObjects( numEvents, hEvents, FALSE, 100 );
        // [rad] Process events.

        if ( nEventIdx == WAIT_TIMEOUT )
        {
             continue;
        }

        if ( WAIT_OBJECT_0 == nEventIdx )
        {
             continueProcessing = false;
             break;
        }

        if ( WAIT_OBJECT_0 == WaitForSingleObject( m_hNextColorFrameEvent, 0 ) )
        {
              emit eventFrameColor();
        }
        usleep(15);
    }
}


//--
void
KinectThread::stop()
{
    continueProcessing = false;
}


//--
void
KinectThread::setColorHandles(HANDLE stream, HANDLE frame)
{
    m_hNextColorFrameEvent = frame;
    m_pVideoStreamHandle = stream;
}

