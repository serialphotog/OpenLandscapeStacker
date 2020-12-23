#include "sidebar.h"

#include <QAction>
#include <QHBoxLayout>
#include <QMenu>

#include "ui/models/frame_tree_nodes.h"
#include "ui/main_window.h"

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

        // Register the action handlers
        addActions(parent);

        // Build the frames tree view
        initFramesTreeView();
    }

    Sidebar::~Sidebar()
    {
        delete m_treeView;
        delete m_lightFramesNode;
        delete m_darkFramesNode;
        delete m_treeModel;
    }

    void Sidebar::addActions(QWidget *parent)
    {
        OLS::MainWindow *win = (OLS::MainWindow*)parent;
        connect(win, SIGNAL(lightFramesAdded(OLS::FrameStore*)), this, 
            SLOT(updateLightFramesView(OLS::FrameStore*)));
        connect(win, SIGNAL(darkFramesAdded(OLS::FrameStore*)), this,
            SLOT(updateDarkFramesView(OLS::FrameStore*)));
        connect(win, SIGNAL(lightFramesCleared()), this, SLOT(clearLightFramesFromView()));
        connect(win, SIGNAL(darkFramesCleared()), this, SLOT(clearDarkFramesFromView()));
    }

    void Sidebar::initFramesTreeView()
    {
        // Disable node editing
        m_treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Custom context menu
        m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, 
            SLOT(onCustomTreeContextMenuRequested(const QPoint &)));

        // Build the root nodes
        m_treeModel = new QStandardItemModel();
        m_lightFramesNode = new OLS::FrameItem(tr("Light Frames"));
        m_lightFramesNode->setTag(OLS::FrameTreeNodes::NODE_LIGHT_FRAMES);
        m_darkFramesNode = new OLS::FrameItem(tr("Dark Frames"));
        m_darkFramesNode->setTag(OLS::FrameTreeNodes::NODE_DARK_FRAMES);

        m_treeModel->appendRow(m_lightFramesNode);
        m_treeModel->appendRow(m_darkFramesNode);
        m_treeView->setModel(m_treeModel);

        // Tree properties
        m_treeView->setRootIsDecorated(true);
        m_treeView->setHeaderHidden(true);
        m_treeView->setIndentation(10);
    }

    void Sidebar::onCustomTreeContextMenuRequested(const QPoint &point)
    {
        QModelIndex idx = m_treeView->indexAt(point);
        if (idx.isValid())
        {
            OLS::FrameItem *item = (OLS::FrameItem*)m_treeModel->itemFromIndex(idx);
            if (item->getTag() == OLS::FrameTreeNodes::NODE_DARK_FRAMES
                || item->getTag() == OLS::FrameTreeNodes::NODE_LIGHT_FRAMES)
            {
                // This is a root node item...
                buildRootTreeNodeContextMenu(item->getTag(), point);
            }
            else
            {
                // This is an individual frame item...
            }
        }
    }

    void Sidebar::buildRootTreeNodeContextMenu(int nodeTag, const QPoint &point) 
    {
        QMenu *menu = new QMenu(m_treeView);
        QAction *addFramesAct;
        QAction *clearFramesAct;

        switch (nodeTag)
        {
            case OLS::FrameTreeNodes::NODE_DARK_FRAMES:
            {
                addFramesAct = new QAction(tr("Add Dark Frames"), this);
                clearFramesAct = new QAction(tr("Clear All Dark Frames"), this);
                connect(addFramesAct, SIGNAL(triggered()), this, SLOT(requestDarkFrames()));
                connect(clearFramesAct, SIGNAL(triggered()), this, SLOT(clearDarkFrames()));
                break;
            }
            case OLS::FrameTreeNodes::NODE_LIGHT_FRAMES:
            {
                addFramesAct = new QAction(tr("Add Light Frames"), this);
                clearFramesAct = new QAction(tr("Clear All Light Frames"), this);
                connect(addFramesAct, SIGNAL(triggered()), this, SLOT(requestLightFrames()));
                connect(clearFramesAct, SIGNAL(triggered()), this, SLOT(clearLightFrames()));
                break;
            }
        }

        menu->addAction(addFramesAct);
        menu->addAction(clearFramesAct);
        menu->exec(m_treeView->viewport()->mapToGlobal(point));
    }

    void Sidebar::updateLightFramesView(OLS::FrameStore *store)
    {
        // Start from a clean slate
        m_lightFramesNode->removeRows(0, m_lightFramesNode->rowCount());

        // Update the view
        for (std::pair<std::string, OLS::Frame*> elem : *store)
        {
            FrameItem* item = new FrameItem(QString::fromStdString(elem.second->getFileName()));
            item->setTag(OLS::FrameTreeNodes::NODE_STANDARD_LIGHT_FRAME_ENTRY);
            m_lightFramesNode->appendRow(item);
        }
    }

    void Sidebar::clearLightFramesFromView()
    {
        m_lightFramesNode->removeRows(0, m_lightFramesNode->rowCount());
    }

    void Sidebar::updateDarkFramesView(OLS::FrameStore *store)
    {
        // Start from a clean slate
        m_darkFramesNode->removeRows(0, m_darkFramesNode->rowCount());

        // Update the view
        for (std::pair<std::string, OLS::Frame*> elem : *store)
        {
            FrameItem *item = new FrameItem(QString::fromStdString(elem.second->getFileName()));
            item->setTag(OLS::FrameTreeNodes::NODE_STANDARD_DARK_FRAME_ENTRY);
            m_darkFramesNode->appendRow(item);
        }
    }

    void Sidebar::clearDarkFramesFromView()
    {
        m_darkFramesNode->removeRows(0, m_darkFramesNode->rowCount());
    }

    void Sidebar::requestDarkFrames()
    {
        emit darkFramesRequested();
    }

    void Sidebar::requestLightFrames()
    {
        emit lightFramesRequested();
    }

    void Sidebar::clearDarkFrames()
    {
        emit clearDarkFramesRequested();
    }

    void Sidebar::clearLightFrames() 
    {
        emit clearLightFramesRequested();
    }
}