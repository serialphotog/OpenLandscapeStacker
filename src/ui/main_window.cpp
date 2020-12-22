#include "main_window.h"

#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

namespace OLS
{

  MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  {
    // Set up some window defaults
    setWindowTitle(tr("Open Landscape Stacker"));
    resize(OLS_WINDOW_WIDTH, OLS_WINDOW_HEIGHT);

    // Set up the actions
    createActions();
  }

  MainWindow::~MainWindow()
  {

  }

  void MainWindow::createActions() 
  {
    // File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *exitAct = new QAction(tr("&Exit"), this);
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);
    fileMenu->addAction(exitAct);

    // Help menu
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = new QAction(tr("About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::displayAboutDlg);
    helpMenu->addAction(aboutAct);
  }

  void MainWindow::displayAboutDlg()
  {
    QMessageBox::about(this, tr("About Open Landscape Stacker"),
      tr("A work in progress landscape stacker by Adam Thompson."));
  }

}
