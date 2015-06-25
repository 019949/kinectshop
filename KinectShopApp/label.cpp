#include "label.h"
#include "kinectthread.h"
#include "display.h"
#include "stdafx.h"

#include <QMessageBox>

Label::Label(QLabel* camera_color) :
m_thread(NULL),
m_display_color(NULL),
m_kinect_initialized(false),
m_hNextColorFrameEvent(NULL),
m_pVideoStreamHandle(NULL),
m_camera_color(camera_color)
{
    // Verbindung zur Kinect herstellen
    Nui_Init();
}


//--
Label::~Label()
{
    // Verbindung zur Kinect beenden
    Nui_UnInit();
}


void Label::Nui_Zero()
{
    SafeRelease( m_pNuiSensor );

//        m_pRenderTarget = NULL;
//        m_pBrushJointTracked = NULL;
//        m_pBrushJointInferred = NULL;
//        m_pBrushBoneTracked = NULL;
//        m_pBrushBoneInferred = NULL;
//        ZeroMemory(m_Points,sizeof(m_Points));

//        m_hNextDepthFrameEvent = NULL;
        m_hNextColorFrameEvent = NULL;
//        m_hNextSkeletonEvent = NULL;
//        m_pDepthStreamHandle = NULL;
        m_pVideoStreamHandle = NULL;
//        m_hThNuiProcess = NULL;
//        m_hEvNuiProcessStop = NULL;
//        m_LastSkeletonFoundTime = 0;
//        m_bScreenBlanked = false;
//        m_DepthFramesTotal = 0;
//        m_LastDepthFPStime = 0;
//        m_LastDepthFramesTotal = 0;
//        m_pDrawDepth = NULL;
//        m_pDrawColor = NULL;
//        m_TrackedSkeletons = 0;
//        m_SkeletonTrackingFlags = NUI_SKELETON_TRACKING_FLAG_ENABLE_IN_NEAR_RANGE;
//        m_DepthStreamFlags = 0;
//        ZeroMemory(m_StickySkeletonIds,sizeof(m_StickySkeletonIds));
}

HRESULT Label::Nui_Init( OLECHAR *instanceName )
{
    // Generic creation failure
    if ( NULL == instanceName )
    {
        QMessageBox msg_box;

        msg_box.setText("NULL == instanceName");
        msg_box.exec();

        return E_FAIL;
    }

    HRESULT hr = NuiCreateSensorById( instanceName, &m_pNuiSensor );

    // Generic creation failure
    if ( FAILED(hr) )
    {
        QMessageBox msg_box;

        msg_box.setText("FAILED NuiCreateSensorById( instanceName, &m_pNuiSensor )");
        msg_box.exec();

        return hr;
    }

    SysFreeString(m_instanceId);

    m_instanceId = m_pNuiSensor->NuiDeviceConnectionId();

    return Nui_Init();
}

HRESULT Label::Nui_Init( )
{
    HRESULT  hr;

    if ( !m_pNuiSensor )
    {
        hr = NuiCreateSensorByIndex(0, &m_pNuiSensor);

        if ( FAILED(hr) )
        {
            return hr;
        }

        SysFreeString(m_instanceId);

        m_instanceId = m_pNuiSensor->NuiDeviceConnectionId();
    }

//    m_hNextDepthFrameEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    m_hNextColorFrameEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
//    m_hNextSkeletonEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

    // reset the tracked skeletons, range, and tracking mode
//    SendDlgItemMessage(m_hWnd, IDC_TRACKEDSKELETONS, CB_SETCURSEL, 0, 0);
//    SendDlgItemMessage(m_hWnd, IDC_TRACKINGMODE, CB_SETCURSEL, 0, 0);
//    SendDlgItemMessage(m_hWnd, IDC_RANGE, CB_SETCURSEL, 0, 0);

//    EnsureDirect2DResources();

//    m_pDrawDepth = new DrawDevice( );
//    result = m_pDrawDepth->Initialize( GetDlgItem( m_hWnd, IDC_DEPTHVIEWER ), m_pD2DFactory, DEPTH_IMAGE_WIDTH, DEPTH_IMAGE_HEIGHT, DEPTH_IMAGE_WIDTH * 4 );
//    if ( !result )
//    {
//        MessageBoxResource( IDS_ERROR_DRAWDEVICE, MB_OK | MB_ICONHAND );
//        return E_FAIL;
//    }

//    m_pDrawColor = new DrawDevice( );
//    result = m_pDrawColor->Initialize( GetDlgItem( m_hWnd, IDC_VIDEOVIEW ), m_pD2DFactory, COLOR_IMAGE_WIDTH, COLOR_IMAGE_HEIGHT, COLOR_IMAGE_WIDTH * 4 );
//    if ( !result )
//    {
//        MessageBoxResource( IDS_ERROR_DRAWDEVICE, MB_OK | MB_ICONHAND );
//        return E_FAIL;
//    }

//    m_pDrawProduct = new DrawDevice( );
//    result = m_pDrawProduct->Initialize( GetDlgItem( m_hWnd, IDC_PRODUCTVIEWER ), m_pD2DFactory, PRODUCT_IMAGE_WIDTH, PRODUCT_IMAGE_HEIGHT, PRODUCT_IMAGE_WIDTH * 4 );
//    if ( !result )
//    {
//        MessageBoxResource( IDS_ERROR_DRAWDEVICE, MB_OK | MB_ICONHAND );
//        return E_FAIL;
//    }

//    DWORD nuiFlags = NUI_INITIALIZE_FLAG_USES_AUDIO | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON |  NUI_INITIALIZE_FLAG_USES_COLOR;
    DWORD nuiFlags = NUI_INITIALIZE_FLAG_USES_COLOR;
    hr = m_pNuiSensor->NuiInitialize(nuiFlags);
//    if ( E_NUI_SKELETAL_ENGINE_BUSY == hr )
//    {
//        nuiFlags = NUI_INITIALIZE_FLAG_USES_DEPTH |  NUI_INITIALIZE_FLAG_USES_COLOR;
//        hr = m_pNuiSensor->NuiInitialize( nuiFlags) ;
//    }

    if ( FAILED( hr ) )
    {
        if ( E_NUI_DEVICE_IN_USE == hr )
        {
            QMessageBox msg_box;

            msg_box.setText("Es wird bereits eine Kinect verwendet.");
            msg_box.exec();
        }
        else
        {
            QMessageBox msg_box;

            msg_box.setText("Kinect kann nicht initialisiert werden.");
            msg_box.exec();
        }
        return hr;
    }

//	hr = InitializeAudioStream();
//    if (FAILED(hr))
//    {
//        MessageBoxResource( IDS_ERROR_AUDIOSTREAM , MB_OK | MB_ICONHAND );
//        return hr;
//    }

//    hr = CreateSpeechRecognizer();
//    if (FAILED(hr))
//    {
//        MessageBoxResource( IDS_ERROR_SPEECHSDK , MB_OK | MB_ICONHAND );
//        return hr;
//    }

//    hr = LoadSpeechGrammar();
//    if (FAILED(hr))
//    {
//        MessageBoxResource( IDS_ERROR_GRAMMAR , MB_OK | MB_ICONHAND );
//        return hr;
//    }

//    hr = StartSpeechRecognition();
//    if (FAILED(hr))
//    {
//        MessageBoxResource( IDS_ERROR_RECOGNITION , MB_OK | MB_ICONHAND );
//        return hr;
//    }

//    if ( HasSkeletalEngine( m_pNuiSensor ) )
//    {
//        hr = m_pNuiSensor->NuiSkeletonTrackingEnable( m_hNextSkeletonEvent, m_SkeletonTrackingFlags );
//        if( FAILED( hr ) )
//        {
//            MessageBoxResource( IDS_ERROR_SKELETONTRACKING, MB_OK | MB_ICONHAND );
//            return hr;
//        }
//    }

    hr = m_pNuiSensor->NuiImageStreamOpen(
        NUI_IMAGE_TYPE_COLOR,
        COLOR_IMAGE_RESOLUTION,
        0,
        2,
        m_hNextColorFrameEvent,
        &m_pVideoStreamHandle );

    if ( FAILED( hr ) )
    {
        QMessageBox msg_box;

        msg_box.setText("Videostream konnte nicht geoeffnet werden.");
        msg_box.exec();
        return hr;
    }

    m_display_color = new Display(m_camera_color, 640, 480);

    // Start the Nui processing thread
//    m_hEvNuiProcessStop = CreateEvent( NULL, FALSE, FALSE, NULL );
//    m_hThNuiProcess = CreateThread( NULL, 0, Nui_ProcessThread, this, 0, NULL );

    // Kinectthread erstellen
    m_thread = new KinectThread(this);

    // Verbinde Kinectthread Events
    QObject::connect(m_thread, SIGNAL(eventFrameVideo()), this, SLOT(eventFrameVideo()));

    // Handles festlegen
    m_thread->setColorHandles(m_pVideoStreamHandle, m_hNextColorFrameEvent);

    // Kinectthread starten
    m_thread->start();

    // Die Kinect wurde erfolgreich initialisiert
    m_kinect_initialized = true;

    return hr;
}

void Label::Nui_UnInit( )
{
    // Stop the Nui processing thread
//    if ( NULL != m_hEvNuiProcessStop )
//    {
//        // Signal the thread
//        SetEvent(m_hEvNuiProcessStop);

//        // Wait for thread to stop
//        if ( NULL != m_hThNuiProcess )
//        {
//            WaitForSingleObject( m_hThNuiProcess, INFINITE );
//            CloseHandle( m_hThNuiProcess );
//        }
//        CloseHandle( m_hEvNuiProcessStop );
//    }

    m_thread->stop();

    if ( m_pNuiSensor )
    {
        m_pNuiSensor->NuiShutdown( );
    }
//    if ( m_hNextSkeletonEvent && ( m_hNextSkeletonEvent != INVALID_HANDLE_VALUE ) )
//    {
//        CloseHandle( m_hNextSkeletonEvent );
//        m_hNextSkeletonEvent = NULL;
//    }
//    if ( m_hNextDepthFrameEvent && ( m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE ) )
//    {
//        CloseHandle( m_hNextDepthFrameEvent );
//        m_hNextDepthFrameEvent = NULL;
//    }
    if ( m_hNextColorFrameEvent && ( m_hNextColorFrameEvent != INVALID_HANDLE_VALUE ) )
    {
        CloseHandle( m_hNextColorFrameEvent );
        m_hNextColorFrameEvent = NULL;
    }

    SafeRelease( m_pNuiSensor );

    // clean up Direct2D graphics
//    delete m_pDrawDepth;
//    m_pDrawDepth = NULL;

//    delete m_pDrawColor;
//    m_pDrawColor = NULL;

//    delete m_pDrawProduct;
//    m_pDrawProduct = NULL;

//    DiscardDirect2DResources();

    // Kinectthread löschen
    //delete(m_thread);

    // Display Objekte löschen
    //delete(m_display_depth);
    //delete(m_display_color);
}


//--
void
Label::eventFrameColor() //Nui_GotColorAlert()
{
    NUI_IMAGE_FRAME imageFrame;

    HRESULT hr = m_pNuiSensor->NuiImageStreamGetNextFrame(
            m_pVideoStreamHandle,
            0,
            &imageFrame );

    if(FAILED(hr))
    {
        return;
    }

    INuiFrameTexture * pTexture = imageFrame.pFrameTexture;
    NUI_LOCKED_RECT LockedRect;
    pTexture->LockRect( 0, &LockedRect, NULL, 0 );

    if(LockedRect.Pitch != 0)
    {
        m_display_color->DrawColor((const unsigned char*) LockedRect.pBits);
    }

    pTexture->UnlockRect(0);

    m_pNuiSensor->NuiImageStreamReleaseFrame(m_pVideoStreamHandle, &imageFrame);
}
