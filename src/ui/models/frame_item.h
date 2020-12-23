#ifndef __FRAME_ITEM_H__
#define __FRAME_ITEM_H__

#include <QStandardItem>
#include <QString>

namespace OLS
{
    // An item that allows assigning a custom tag to more easily identify it.
    class FrameItem : public QStandardItem
    {
        public:
            FrameItem(const QString &text) : QStandardItem(text) { };
            int getTag() const { return m_tag; }
            void setTag(int tag) { this->m_tag = tag; }
        private:
            int m_tag; 
    };
}

#endif