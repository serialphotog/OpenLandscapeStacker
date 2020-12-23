#ifndef __FRAME_STORE_H__
#define __FRAME_STORE_H__

#include <unordered_map>

#include "core/frame.h"

namespace OLS 
{
    class FrameStore
    {
        // Data type definitions
        using data_t = std::unordered_map<std::string, OLS::Frame*>;
        using iterator = data_t::iterator;
        using const_iterator = data_t::const_iterator;

        public:
            FrameStore();
            ~FrameStore();

            // Inserts a new frame into the framestore
            void insert(std::string fileName, OLS::Frame* frame);

            // Removes all items from the framestore
            void clear();

            // Checks if the framestore contains a given key
            bool containsKey(const std::string &key) const;

            // Removes a specific item from the store based on the key
            void remove(const std::string &key);

            // Gets a specific frame based on the key
            OLS::Frame* getFrame(const std::string &key);

            // Iterators
            iterator begin() { return m_data.begin(); }
            iterator end() { return m_data.end(); }
            const_iterator begin() const { return m_data.begin(); }
            const_iterator end() const { return m_data.end(); }
            const_iterator cbegin() const { return m_data.cbegin(); }
            const_iterator cend() const { return m_data.cend(); }

        private:
            // The backing storage for the framestore
            // Keys are file names, values are frames
            data_t m_data;
    };
}

#endif