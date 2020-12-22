#include "sidebar.h"

#include <QHBoxLayout>

namespace OLS 
{
    Sidebar::Sidebar(QWidget *parent) : QWidget(parent)
    {
        // Build the UI
        QHBoxLayout *layout = new QHBoxLayout();
        m_treeView = new QTreeView;
        layout->addWidget(m_treeView);

        // Set the layout
        setLayout(layout);
    }

    Sidebar::~Sidebar()
    {
        delete m_treeView;
    }
}