#include "frame.h"

#include "core/util/filesystem.h"

namespace OLS 
{

    Frame::Frame(const std::string &path, OLS::FrameType type) : m_filePath(path), m_type(type)
    {
        m_fileName = FileSystem::getFileNameFromPath(path);
    }

    Frame::~Frame() 
    {

    }

}