#ifndef __PREVIEW_H__
#define __PREVIEW_H__

#include <QWidget>

namespace OLS
{
    // The preview area of the application
    class Preview : public QWidget
    {
        Q_OBJECT
        public:
           explicit Preview(QWidget *parent = 0);
            ~Preview();
    };
}

#endif