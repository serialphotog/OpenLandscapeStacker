#ifndef __FRAME_H__
#define __FRAME_H__

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
            Frame(OLS::FrameType type);
            ~Frame();

            // Returns the type of this frame
            OLS::FrameType getType() { return m_type; }
        
        private:
            // The type of this frame
            OLS::FrameType m_type;
    };
}

#endif