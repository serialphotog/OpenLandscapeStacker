#include "main_window.h"

#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>

namespace OLS
{

  // The stylesheet for the primary splitter
  const QString splitterStyle = \
  "QSplitter:handle { \
    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, \
    stop: 0 #eee, stop:1 #ccc); \
    border: 1px soild #777; \
    width: 13px; \
    margin-top: 10px; \
    margin-bottom: 10px; \
    margin-left: 2px; \
    margin-rigth: 2px; \
    border-radius: 4px; \
  }";

  MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  {
    // Set up some window defaults
    setWindowTitle(tr("Open Landscape Stacker"));
    resize(OLS_WINDOW_WIDTH, OLS_WINDOW_HEIGHT);

    // Build the main UI
    m_splitter = new QSplitter(parent);
    m_splitter->setStyleSheet(splitterStyle);
    m_previewWidget = new OLS::Preview();
    m_sidebarWidget = new OLS::Sidebar();
    m_splitter->addWidget(m_sidebarWidget);
    m_splitter->addWidget(m_previewWidget);
    this->setCentralWidget(m_splitter);

    // Set up the actions
    createActions();
  }

  MainWindow::~MainWindow()
  {
    delete m_previewWidget;
    delete m_sidebarWidget;
    delete m_splitter;
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
