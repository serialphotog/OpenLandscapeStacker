#include "preview.h"

#include <QDebug>

#include <QImage>
#include <QImageReader>
#include <QPalette>
#include <QPixmap>
#include <QSizePolicy>
#include <QVBoxLayout>

namespace OLS
{
    Preview::Preview(QWidget *parent) : QWidget(parent)
    {
        // Build the UI
        QVBoxLayout *layout = new QVBoxLayout();
        m_previewScrollArea = new QScrollArea();
        m_imagePreview = new QLabel();
        layout->addWidget(m_previewScrollArea);

        // Set the layout 
        setLayout(layout);
        initImagePreviewViewArea();
    }

    Preview::~Preview()
    {
        delete m_imagePreview;
        delete m_previewScrollArea;
    }

    void Preview::initImagePreviewViewArea()
    {
        m_imagePreview->setBackgroundRole(QPalette::Base);
        m_imagePreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_imagePreview->setScaledContents(true);
        m_previewScrollArea->setWidgetResizable(true);
        m_previewScrollArea->setBackgroundRole(QPalette::Dark);
        m_previewScrollArea->setVisible(false);
        m_previewScrollArea->setWidget(m_imagePreview);
    }

    void Preview::resizeEvent(QResizeEvent *event)
    {
        fitWithAspect();
    }

    void Preview::clear()
    {
        m_imagePreview->clear();
        m_previewScrollArea->setVisible(false);
    }

    void Preview::updatePreviewImage(const QString &imagePath)
    {
        m_previewImage = imread(imagePath.toStdString(), cv::IMREAD_COLOR);
        m_previewScrollArea->setVisible(true);
        fitWithAspect();
    }

    void Preview::fitWithAspect()
    {
        if (!m_previewImage.empty())
        {
            QImage img = QImage((uchar*) m_previewImage.data, m_previewImage.cols, 
                m_previewImage.rows, m_previewImage.step, QImage::Format_RGB888); 
            int width = m_imagePreview->width();
            int height = m_imagePreview->height();
            QPixmap pix = QPixmap::fromImage(img);
            m_imagePreview->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
        }
    }
}