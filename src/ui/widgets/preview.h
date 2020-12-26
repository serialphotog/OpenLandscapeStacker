#ifndef __PREVIEW_H__
#define __PREVIEW_H__

#include <QLabel>
#include <QScrollArea>
#include <QString>
#include <QWidget>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

// Defines the boudns for zoom controls
#define ZOOM_UPPER_BOUND 3.0
#define ZOOM_LOWER_BOUND 0.111

namespace OLS
{
    // The preview area of the application
    class Preview : public QWidget
    {
        Q_OBJECT

        public:
           explicit Preview(QWidget *parent = 0);
            ~Preview();

            // Updates the preview image
            void updatePreviewImage(const QString &imagePath);

            // Clears the preview area
            void clear();

        private:
            // The preview image
            cv::Mat m_previewImage;

            // The scroll area that contains the image preview
            QScrollArea *m_previewScrollArea;

            // The label that displays the image preview
            QLabel *m_imagePreview;

            // Initializes the image preview view
            void initImagePreviewViewArea();

            // Fits an image to the preview view while maintaining aspect ratio
            void fitWithAspect();

            // Handles the resize event
            void resizeEvent(QResizeEvent *event) override;
    };
}

#endif