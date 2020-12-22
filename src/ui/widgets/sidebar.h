#ifndef __SIDEBAR_H__
#define __SIDEBAR_H__

#include <QWidget>
#include <QTreeView>

namespace OLS
{

    // The sidebar of the application
    class Sidebar : public QWidget
    {
        Q_OBJECT
        public:
            explicit Sidebar(QWidget *parent = 0);
            ~Sidebar();

        private:
            QTreeView *m_treeView;
    };

}

#endif