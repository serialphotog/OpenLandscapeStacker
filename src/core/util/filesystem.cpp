#include "filesystem.h"

#include <QFileInfo>
#include <QString>

namespace OLS
{
    std::string FileSystem::getFileNameFromPath(const std::string &path)
    {
        QFileInfo info(QString::fromStdString(path));
        return info.fileName().toStdString();
    }
}