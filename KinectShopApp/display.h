#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QLabel>

class Display : public QObject
{
    Q_OBJECT

    public:

        Display(QLabel* label, unsigned int width, unsigned int height, QObject* parent = NULL);
        virtual ~Display();

    public:

        void DrawColor(const unsigned char* data);

    protected:

        QLabel* m_label;

        unsigned int m_width;
        unsigned int m_height;
};

#endif // DISPLAY_H
