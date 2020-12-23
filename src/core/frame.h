#ifndef __FRAME_H__
#define __FRAME_H__

#include <string>

namespace OLS
{
    // The various types of frames available
    enum FrameType
    {
        FRAME_LIGHT = 0x01, // A light frame
        FRAME_DARK = 0x02, // A dark (noise) frame
        FRAME_COMPOSITE = 0x03 // The composite frame
    };

    class Frame
    {
        public:
            Frame() = delete;
            Frame(const std::string &path, OLS::FrameType type);
            ~Frame();

            OLS::FrameType getType() { return m_type; }
            std::string getFileName() const { return m_fileName; }
            std::string getFilePath() const { return m_filePath; }
        
        private:
            // The type of this frame
            OLS::FrameType m_type;

            // The path to the frame on disk
            std::string m_filePath;

            // The file name for the frame
            std::string m_fileName;
    };
}

#endif