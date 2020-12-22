#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QWidget>

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
      // Creates the actions for the main window
      void createActions();
  };

}

#endif
