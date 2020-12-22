#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QSplitter>
#include <QWidget>

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

    private slots:
      // Displays the about dialog
      void displayAboutDlg();

    private:
      // The primary splitter
      QSplitter *m_splitter;

      // The sidebar and preview widgets
      OLS::Preview *m_previewWidget;
      OLS::Sidebar *m_sidebarWidget;

      // Creates the actions for the main window
      void createActions();
  };

}

#endif
