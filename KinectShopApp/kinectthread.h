#ifndef KINECTTHREAD_H
#define KINECTTHREAD_H

#include <QtCore/QThread>

#include <Windows.h>
#include <NuiApi.h>


class KinectThread : public QThread
{
    Q_OBJECT

    public:

        KinectThread(QObject* parent = NULL);
        virtual ~KinectThread();

    public:
        void setColorHandles(HANDLE stream, HANDLE frame);

    public:

        void stop();

    protected:

        void run();

    signals:
        void eventFrameColor();

    protected:
        bool continueProcessing;

        HANDLE m_hNextColorFrameEvent;

        HANDLE m_pVideoStreamHandle;
};

#endif // KINECTTHREAD_H
