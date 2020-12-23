#include "main_window.h"

#include <QDebug>
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
    margin-right: 2px; \
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
    m_previewWidget = new OLS::Preview(this);
    m_sidebarWidget = new OLS::Sidebar(this);
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

    // Hanlde signals from the sidebar
    connect(m_sidebarWidget, SIGNAL(darkFramesRequested()), this, 
        SLOT(requestDarkFramesFromUser()));
    connect(m_sidebarWidget, SIGNAL(lightFramesRequested()), this, 
        SLOT(requestLightFramesFromUser()));
    connect(m_sidebarWidget, SIGNAL(clearDarkFramesRequested()), this, SLOT(clearDarkFrames()));
    connect(m_sidebarWidget, SIGNAL(clearLightFramesRequested()), this, SLOT(clearLightFrames()));
  }

  void MainWindow::displayAboutDlg()
  {
    QMessageBox::about(this, tr("About Open Landscape Stacker"),
      tr("A work in progress landscape stacker by Adam Thompson."));
  }

  void MainWindow::requestLightFramesFromUser() 
  {
    qDebug() << "Request light frames";
  }

  void MainWindow::requestDarkFramesFromUser()
  {
    qDebug() << "Request dark frames";
  }

  void MainWindow::clearLightFrames()
  {
    qDebug() << "Clear light frames";
  }

  void MainWindow::clearDarkFrames()
  {
    qDebug() << "Clear dark frames";
  }

}
