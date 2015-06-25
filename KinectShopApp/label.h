#ifndef LABEL_H
#define LABEL_H

#define COLOR_IMAGE_RESOLUTION NUI_IMAGE_RESOLUTION_1280x960
#define COLOR_IMAGE_WIDTH 1280
#define COLOR_IMAGE_HEIGHT 960
#define DEPTH_IMAGE_RESOLUTION NUI_IMAGE_RESOLUTION_320x240
#define DEPTH_IMAGE_WIDTH 320
#define DEPTH_IMAGE_HEIGHT 240

#include <QObject>
#include <QLabel>
#include <Windows.h>
#include <NuiApi.h>

class KinectThread;
class Display;

class Label : public QObject
{
    Q_OBJECT

    public:

        Label(QLabel* camera_color);
        virtual ~Label();

    public slots:
        void eventFrameColor();

    protected:
        void Nui_Zero();
        HRESULT Nui_Init();
        HRESULT Nui_Init( OLECHAR * instanceName );
        void Nui_UnInit();

    protected:
        KinectThread* m_thread;

        Display* m_display_color;

        bool m_kinect_initialized;

        HANDLE m_hNextColorFrameEvent;

        HANDLE m_pVideoStreamHandle;

        QLabel* m_camera_color;

        // Current kinect
        INuiSensor *            m_pNuiSensor;
        BSTR                    m_instanceId;
};

#endif // LABEL_H
