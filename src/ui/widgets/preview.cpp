#include "preview.h"

#include <QImage>
#include <QImageReader>
#include <QPalette>
#include <QPixmap>
#include <QSizePolicy>
#include <QVBoxLayout>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

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

    void Preview::clear()
    {
        m_imagePreview->clear();
        m_previewScrollArea->setVisible(false);
    }

    void Preview::updatePreviewImage(const QString &imagePath)
    {
        cv::Mat cvimg = imread(imagePath.toStdString(), cv::IMREAD_COLOR);
        QImage img = QImage((uchar*) cvimg.data, cvimg.cols, cvimg.rows, cvimg.step, 
            QImage::Format_RGB888); 
        m_previewScrollArea->setVisible(true);
        m_imagePreview->setPixmap(QPixmap::fromImage(img));
        m_imagePreview->adjustSize();
    }
}