#ifndef __SIDEBAR_H__
#define __SIDEBAR_H__

#include <QPoint>
#include <QStandardItemModel>
#include <QTreeView>
#include <QWidget>

#include "ui/models/frame_item.h"
#include "core/frame_store.h"

namespace OLS
{

    // The sidebar of the application
    class Sidebar : public QWidget
    {
        Q_OBJECT
        public:
            explicit Sidebar(QWidget *parent = 0);
            ~Sidebar();

        private slots:
            // Handles the custom context menu for the tree view
            void onCustomTreeContextMenuRequested(const QPoint &point);

            // Slots for the tree view context menu items
            void requestDarkFrames();
            void requestLightFrames();
            void clearDarkFrames();
            void clearLightFrames();

            // Slots for updating the UI
            void updateLightFramesView(OLS::FrameStore *store);
            void updateDarkFramesView(OLS::FrameStore *store);
            void clearLightFramesFromView();
            void clearDarkFramesFromView();

        signals:
            // Tree item signals
            void darkFramesRequested();
            void lightFramesRequested();
            void clearDarkFramesRequested();
            void clearLightFramesRequested();

        private:
            // The frames tree view
            QTreeView *m_treeView;

            // The item model for the frames tree view
            QStandardItemModel *m_treeModel;

            // The root nodes for the frames tree
            OLS::FrameItem *m_lightFramesNode;
            OLS::FrameItem *m_darkFramesNode;

            // Adds the action handlers
            void addActions(QWidget *parent);

            // Initializes the frames tree view
            void initFramesTreeView();

            // Builds the context menu for a root tree item
            void buildRootTreeNodeContextMenu(int nodeTag, const QPoint &point);
    };

}

#endif