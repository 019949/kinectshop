greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
folder_source.source = src
folder_source.target = .
folder_css.source = src/css
folder_css.target = .
folder_js.source = src/js
folder_js.target = .
folder_img.source = src/img
folder_img.target = .
folder_fonts.source = src/fonts
folder_fonts.target = .
DEPLOYMENTFOLDERS += folder_source folder_css folder_js folder_img folder_fonts

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    sqlfunctions.cpp \
    product.cpp \
    automaton.cpp \
    state.cpp

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

#OTHER_FILES += \
#    html/styles.css \
#    html/functions.js \

# QT SQL-Connection
QT += sql

HEADERS += \
    sqlfunctions.h \
    product.h \
    automaton.h \
    state.h
