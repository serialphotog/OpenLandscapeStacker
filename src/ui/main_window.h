#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QSplitter>
#include <QStringList>
#include <QWidget>

#include "core/frame_store.h"
#include "core/stack_manager.h"
#include "ui/widgets/preview.h"
#include "ui/widgets/sidebar.h"

#define OLS_WINDOW_WIDTH 650
#define OLS_WINDOW_HEIGHT 500

namespace OLS
{

  class MainWindow : public QMainWindow
  {
    Q_OBJECT

    public:
      MainWindow(QWidget *parent = nullptr);
      ~MainWindow();

    signals:
      void lightFramesAdded(OLS::FrameStore *store);
      void darkFramesAdded(OLS::FrameStore *store);
      void lightFramesCleared();
      void darkFramesCleared();

    private slots:
      // Displays the about dialog
      void displayAboutDlg();

      // Slots for dealing with context actions on tree items
      void requestLightFramesFromUser();
      void requestDarkFramesFromUser();
      void clearDarkFrames();
      void clearLightFrames();

    private:
      // The stack manager instance
      OLS::StackManager *m_stackManager;

      // The primary splitter
      QSplitter *m_splitter;

      // The sidebar and preview widgets
      OLS::Preview *m_previewWidget;
      OLS::Sidebar *m_sidebarWidget;

      // Creates the actions for the main window
      void createActions();

      //Requests supported image files from the user
      QStringList getImageFilesFromUser() const;
  };

}

#endif
