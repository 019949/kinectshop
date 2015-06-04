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

    // Sprachsteuerung des Automaten //////////////////////////////////////////////////////////////////
    automaton automA;
    automA.setObj(&obj);

    /*
    // Zustände
    #define START 0
    #define SELECTED 1
    #define AMOUNTSET 2
    #define END 3

    state start, selected, amountset, end;

    // Eingaben
    // Mengen
    #define ONE 1
    #define TWO 2
    //  andere Befehle
    #define SELECT 100
    #define PUTINCART 101
    #define BACK 102
    #define CANCEL 103
    #define MORE 104

    // Transitionen des Automaten
    // Trasition im "Normalfall"
    transition(start, selected, SELECT, &automA);
    transition(selected, amountset, ONE, &automA);
    transition(selected, amountset, TWO, &automA);
    transition(amountset, end, PUTINCART, &automA);

    // "Zurück-, Mehr- und Abbrechen-Transitionen"
    transition(selected, start, BACK, &automA);
    transition(amountset, selected, BACK, &automA);
    transition(end, start, MORE, &automA);
    transition(selected, start, CANCEL, &automA);
    transition(amountset, start, CANCEL, &automA);
    */

    // ---------------------------- //////////////////////////////////////////////////////////////////

    /*QObject::connect(&obj,SIGNAL(cartChanged()),&obj,SLOT(showCart())); // showCart() muss im js*/

    // Den Shop initialisieren //////////////////////////////////////////////////////////////////

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("src/index.html"));
    viewer.setFixedSize(1200, 900);

    QWebFrame *frame = viewer.webView()->page()->mainFrame();
    QString sqlObjName = "mySqlObj";
    QString automatonObjName = "automaton";
    frame->addToJavaScriptWindowObject(sqlObjName, &obj);
    frame->addToJavaScriptWindowObject(automatonObjName, &automA);

    return app.exec();
}
