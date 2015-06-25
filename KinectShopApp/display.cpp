#include "display.h"

Display::Display(QLabel* label, unsigned int width, unsigned int height, QObject* parent) :
m_label(label),
QObject(parent),
m_width(width),
m_height(height)
{
}


//--
Display::~Display()
{
}


//--
void
Display::DrawColor(const unsigned char* data)
{
    QImage qimage((const unsigned char*) data, m_width, m_height, QImage::Format_RGB32);
    m_label->setPixmap(QPixmap::fromImage(qimage.scaled(m_label->frameSize())));
}

