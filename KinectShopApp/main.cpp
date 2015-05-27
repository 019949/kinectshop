#include <QApplication>

#include <QGraphicsWebView>
#include <QWebFrame>
#include <QtWebKit>

#include "html5applicationviewer.h"

#include "sqlfunctions.h"
#include "automaton.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    sqlfunctions obj;
    automaton autoObj;
    autoObj.setObj(&obj);

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("src/index.html"));
    viewer.setFixedSize(1200, 900);

    QWebFrame *frame = viewer.webView()->page()->mainFrame();
    QString sqlObjName = "mySqlObj";
    QString automatonObjName = "automaton";
    frame->addToJavaScriptWindowObject(sqlObjName, &obj);
    frame->addToJavaScriptWindowObject(automatonObjName, &autoObj);

    return app.exec();
}
