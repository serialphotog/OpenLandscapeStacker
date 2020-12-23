#include "frame_store.h"

namespace OLS
{
    FrameStore::FrameStore()
    {

    }

    FrameStore::~FrameStore()
    {
        for (std::unordered_map<std::string, OLS::Frame*>::iterator itr = m_data.begin();
            itr != m_data.end(); itr++)
        {
            delete (itr->second);
        }
        m_data.clear();
    }

    void FrameStore::insert(std::string fileName, OLS::Frame *frame)
    {
        m_data.insert(make_pair(fileName, frame));
    }

    void FrameStore::clear()
    {
        m_data.clear();
    }

    bool FrameStore::containsKey(const std::string &key) const 
    {
        for (std::pair<std::string, OLS::Frame*> elem : m_data)
        {
            if (elem.first == key)
                return true;
        }
        return false;
    }

    void FrameStore::remove(const std::string &key)
    {
        m_data.erase(key);
    }

    OLS::Frame* FrameStore::getFrame(const std::string &key)
    {
        return m_data[key];
    }
}