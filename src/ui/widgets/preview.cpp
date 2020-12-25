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

    void Preview::updatePreviewImage(const QString &imagePath)
    {
        QImageReader reader(imagePath);
        // TODO: Scaling...
        m_previewScrollArea->setVisible(true);
        QImage img = reader.read();
        qDebug() << reader.errorString();
        m_imagePreview->setPixmap(QPixmap::fromImageReader(&reader));
        m_imagePreview->adjustSize();
    }
}