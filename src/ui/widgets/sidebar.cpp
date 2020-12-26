#include "sidebar.h"

#include <QAction>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSignalMapper>
#include <QStringList>
#include <QVboxLayout>

#include <string>

#include "ui/models/frame_tree_nodes.h"
#include "ui/main_window.h"

namespace OLS 
{
    Sidebar::Sidebar(QWidget *parent) : QWidget(parent)
    {
        // Build the UI
        QVBoxLayout *layout = new QVBoxLayout();
        m_treeView = new QTreeView;
        layout->addWidget(m_treeView);

        // Preview selection box
        m_previewSelectionBox = new QComboBox(this);
        connect(m_previewSelectionBox, SIGNAL(currentTextChanged(const QString&)), 
            this, SLOT(previewBoxChangeRequested(const QString&)));
        QGroupBox *previewGroup = new QGroupBox();
        QHBoxLayout *previewGroupLayout = new QHBoxLayout();
        QLabel *lblPreview = new QLabel(tr("Preview:"));
        previewGroupLayout->addWidget(lblPreview);
        previewGroupLayout->addWidget(m_previewSelectionBox);
        previewGroup->setLayout(previewGroupLayout);
        layout->addWidget(previewGroup);

        // Button Controls
        QGroupBox *buttonGroup = new QGroupBox();
        QHBoxLayout *buttonGroupLayout = new QHBoxLayout();
        QPushButton *btnAlign = new QPushButton(tr("Align"));
        QPushButton *btnStack = new QPushButton(tr("Stack"));
        // TODO: Connections
        buttonGroupLayout->addWidget(btnAlign);
        buttonGroupLayout->addWidget(btnStack);
        buttonGroup->setLayout(buttonGroupLayout);
        layout->addWidget(buttonGroup);

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
        delete m_previewSelectionBox;
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
                QMenu *menu = new QMenu(m_treeView);
                QAction *removeFrameAct = new QAction(tr("Remove Frame"), this);

                QSignalMapper mapper;
                connect(removeFrameAct, SIGNAL(triggered()), &mapper, SLOT(map()));
                mapper.setMapping(removeFrameAct, (QObject*)item);

                if (item->getTag() == OLS::FrameTreeNodes::NODE_STANDARD_LIGHT_FRAME_ENTRY)
                {
                   connect(&mapper, SIGNAL(mappedObject(QObject*)), this,
                        SLOT(deleteLightFrame(QObject*)));
                }
                else 
                {
                    connect(&mapper, SIGNAL(mappedObject(QObject*)), this,
                        SLOT(deleteDarkFrame(QObject*)));
                }

                menu->addAction(removeFrameAct);
                menu->exec(m_treeView->viewport()->mapToGlobal(point));
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

    void Sidebar::previewBoxChangeRequested(const QString &item)
    {
        if (!item.trimmed().isEmpty())
        {
            // Signal the change
            emit previewFrameDidChange(item);
        }
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

        // Update the preview combobox
        updatePreviewSelectionBox(store);
    }

    void Sidebar::updatePreviewSelectionBox(OLS::FrameStore *store)
    {
        // Convert the framestore into a QStringList
        QStringList previewList;
        for (std::pair<std::string, OLS::Frame*> elem : *store)
        {
            previewList.append(QString::fromStdString(elem.first));
        }

        // Clear the original items
        m_previewSelectionBox->clear();
        m_previewSelectionBox->addItems(previewList);
    }

    void Sidebar::removeSinglePreviewBoxEntry(const QString &item)
    {
        QStringList previewItems;
        for (int i = 0; i < m_previewSelectionBox->count(); i++)
        {
            previewItems << m_previewSelectionBox->itemText(i);
        }

        int idx = previewItems.indexOf(item);
        if (idx >= 0)
        {
            previewItems.remove(idx);
            m_previewSelectionBox->clear();
            m_previewSelectionBox->addItems(previewItems);
        }

        if (previewItems.size() == 0)
            emit allLightFramesRemoved();
    }

    void Sidebar::clearLightFramesFromView()
    {
        m_lightFramesNode->removeRows(0, m_lightFramesNode->rowCount());
        
        // Clear the preview box
        m_previewSelectionBox->clear();
        emit allLightFramesRemoved();
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

    void Sidebar::deleteLightFrame(QObject *item)
    {
        OLS::FrameItem *frameItem = (OLS::FrameItem*)item;
        std::string frame = frameItem->text().toStdString();
        m_lightFramesNode->removeRow(frameItem->row());

        // Remove the item from teh preview box
        removeSinglePreviewBoxEntry(QString::fromStdString(frame));

        emit deleteLightFrameRequested(frame);
    }

    void Sidebar::deleteDarkFrame(QObject *item)
    {
        OLS::FrameItem *frameItem = (OLS::FrameItem*)item;
        std::string frame = frameItem->text().toStdString();
        m_darkFramesNode->removeRow(frameItem->row());
        emit deleteDarkFrameRequested(frame);
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