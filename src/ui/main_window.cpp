#include "main_window.h"

#include <QFileDialog>  
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>  
#include <QStandardPaths>
#include <QString>

#include "core/frame.h"
#include "core/settings.h"

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

    // Initialize the stack manager
    m_stackManager = new OLS::StackManager();

    // Build the main UI
    m_splitter = new QSplitter(parent);
    m_splitter->setStyleSheet(splitterStyle);
    m_previewWidget = new OLS::Preview(this);
    m_sidebarWidget = new OLS::Sidebar(this);
    m_splitter->addWidget(m_sidebarWidget);
    m_splitter->addWidget(m_previewWidget);
    m_splitter->setSizes(QList<int>() << 50 << 400);
    this->setCentralWidget(m_splitter);

    // Set up the actions
    createActions();
  }

  MainWindow::~MainWindow()
  {
    delete m_previewWidget;
    delete m_sidebarWidget;
    delete m_splitter;
    delete m_stackManager;
  }

  void MainWindow::createActions() 
  {
    // File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *addLightFramesAct = new QAction(tr("Add &Light Frames"), this);
    connect(addLightFramesAct, &QAction::triggered, this, 
      &MainWindow::requestLightFramesFromUser);
    fileMenu->addAction(addLightFramesAct);
    QAction *addDarkFramesAct = new QAction(tr("Add &Dark Frames"), this);
    connect(addDarkFramesAct, &QAction::triggered, this,
      &MainWindow::requestDarkFramesFromUser);
    fileMenu->addAction(addDarkFramesAct);
    QAction *clearLightFramesAct = new QAction(tr("Clear Light Frames"), this);
    connect(clearLightFramesAct, &QAction::triggered, this,
      &MainWindow::clearLightFrames);
    fileMenu->addAction(clearLightFramesAct);
    QAction *clearDarkFramesAct = new QAction(tr("Clear Dark Frames"), this);
    connect(clearDarkFramesAct, &QAction::triggered, this,
      &MainWindow::clearDarkFrames);
    fileMenu->addAction(clearDarkFramesAct);
    fileMenu->addSeparator();
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
    connect(m_sidebarWidget, SIGNAL(deleteLightFrameRequested(std::string)), this, 
        SLOT(deleteDarkFrame(std::string)));
    connect(m_sidebarWidget, SIGNAL(deleteDarkFrameRequested(std::string)), this,
        SLOT(deleteDarkFrame(std::string)));
  }

  QStringList MainWindow::getImageFilesFromUser() const 
  {
    QSettings settings;

    // Get the files from the user
    QFileDialog dialog(nullptr, tr("Open Images"));
    dialog.setDirectory(settings.value(OLS::DEFAULT_DIRECTORY_KEY, 
      QStandardPaths::PicturesLocation).toString());
    
    dialog.setNameFilter(tr("Images (*.tif)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
    {
      // Save the directory for next time...
      QDir currentDir;
      settings.setValue(OLS::DEFAULT_DIRECTORY_KEY,
        currentDir.absoluteFilePath(dialog.selectedFiles()[0]));
      return dialog.selectedFiles();
    }

    return QStringList();
  }

  /**
   * SLOTS
   */

  void MainWindow::displayAboutDlg()
  {
    QMessageBox::about(this, tr("About Open Landscape Stacker"),
      tr("A work in progress landscape stacker by Adam Thompson."));
  }

  void MainWindow::requestLightFramesFromUser() 
  {
    QStringList files = getImageFilesFromUser();
    for (QString file : files)
    {
      OLS::Frame *frame = new OLS::Frame(file.toStdString(), OLS::FrameType::FRAME_LIGHT);
      m_stackManager->addLightFrame(frame);
    }

    // Emit the signal to update the sidebar UI
    emit lightFramesAdded(m_stackManager->getLightFramesStore());
  }

  void MainWindow::requestDarkFramesFromUser()
  {
    QStringList files = getImageFilesFromUser();
    for (QString file : files)
    {
      OLS::Frame *frame = new OLS::Frame(file.toStdString(), OLS::FrameType::FRAME_LIGHT);
      m_stackManager->addDarkFrame(frame);
    }

    // Emit the singal to update the sidebar UI
    emit darkFramesAdded(m_stackManager->getDarkFrameStore());
  }

  void MainWindow::clearLightFrames()
  {
    m_stackManager->clearLightFrames();
    emit lightFramesCleared();
  }

  void MainWindow::clearDarkFrames()
  {
    m_stackManager->clearDarkFrames();
    emit darkFramesCleared();
  }

  void MainWindow::deleteLightFrame(const std::string &frameName)
  {
    m_stackManager->removeLightFrame(frameName);
  }

  void MainWindow::deleteDarkFrame(const std::string &frameName)
  {
    m_stackManager->removeDarkFrame(frameName);
  }

}
