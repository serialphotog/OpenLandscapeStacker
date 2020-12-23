#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <string>

namespace OLS
{
    class FileSystem
    {
        public:
            FileSystem() = delete;

            // Gets a filename from a filesystem path
            static std::string getFileNameFromPath(const std::string &path);
    };
}

#endif