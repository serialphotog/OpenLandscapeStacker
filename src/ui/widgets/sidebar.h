#ifndef __SIDEBAR_H__
#define __SIDEBAR_H__

#include <QComboBox>
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

            // Slots for deleting individual frames
            void deleteLightFrame(QObject *item);
            void deleteDarkFrame(QObject *item);

            // Handles preview box change event
            void previewBoxChangeRequested(const QString &item);

        signals:
            // Tree item signals
            void darkFramesRequested();
            void lightFramesRequested();
            void clearDarkFramesRequested();
            void clearLightFramesRequested();

            // Signals for deleting individual items
            void deleteLightFrameRequested(std::string frameName);
            void deleteDarkFrameRequested(std::string frameName);

            // Signals that the preview selection was changed
            void previewFrameDidChange(const QString &frame);

            // Gets fired when all light frames have been removed
            void allLightFramesRemoved();

        private:
            // The frames tree view
            QTreeView *m_treeView;

            // The combobox for the preview frame selection
            QComboBox *m_previewSelectionBox;

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

            // Updates the preview selection combobox when new frames are added
            void updatePreviewSelectionBox(OLS::FrameStore *store);

            // Removes a single entry from the preview combobox
            void removeSinglePreviewBoxEntry(const QString &item);
    };

}

#endif