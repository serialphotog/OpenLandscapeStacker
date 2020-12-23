#ifndef __STACK_MANAGER_H__
#define __STACK_MANAGER_H__

#include <string>

#include "core/frame.h"
#include "core/frame_store.h"

namespace OLS
{
    class StackManager
    {
        public:
            StackManager();
            ~StackManager();

            // Methods for adding frames
            void addLightFrame(OLS::Frame *frame);
            void addDarkFrame(OLS::Frame *frame);

            // Methods for clearing frames
            void clearLightFrames();
            void clearDarkFrames();

            // Methods for removing specific frames
            void removeLightFrame(const std::string &frameName);
            void removeDarkFrame(const std::string &frameName);

            // Methods to retrieve a specific frame
            OLS::Frame* getLightFrame(const std::string &frameName) const;
            OLS::Frame* getDarkFrame(const std::string &frameName) const;

            // Methods for getting the various frame stores
            OLS::FrameStore* getDarkFrameStore() const { return m_darkFrames; }
            OLS::FrameStore* getLightFramesStore() const { return m_lightFrames; }
        
        private:
            // The backing framestores
            OLS::FrameStore *m_darkFrames;
            OLS::FrameStore *m_lightFrames;
    };
}

#endif