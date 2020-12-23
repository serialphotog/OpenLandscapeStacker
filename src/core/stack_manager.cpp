#include "stack_manager.h"

namespace OLS
{
    StackManager::StackManager()
    {
        // Initialize the framestores
        m_darkFrames = new OLS::FrameStore();
        m_lightFrames = new OLS::FrameStore();
    }

    StackManager::~StackManager()
    {
        delete m_darkFrames;
        delete m_lightFrames;
    }

    void StackManager::addLightFrame(OLS::Frame *frame)
    {
        m_lightFrames->insert(frame->getFileName(), frame);
    }

    void StackManager::addDarkFrame(OLS::Frame *frame)
    {
        m_darkFrames->insert(frame->getFileName(), frame);
    }

    void StackManager::clearDarkFrames() 
    {
        m_darkFrames->clear();
    }

    void StackManager::clearLightFrames()
    {
        m_lightFrames->clear();
    }

    void StackManager::removeLightFrame(const std::string &frameName)
    {
        m_lightFrames->remove(frameName);
    }

    void StackManager::removeDarkFrame(const std::string &frameName)
    {
        m_darkFrames->remove(frameName);
    }

    OLS::Frame* StackManager::getLightFrame(const std::string &frameName) const 
    {
        return m_lightFrames->getFrame(frameName);
    }

    OLS::Frame* StackManager::getDarkFrame(const std::string &frameName) const
    {
        return m_darkFrames->getFrame(frameName);
    }
}