#ifndef __FRAME_TREE_NODES_H__
#define __FRAME_TREE_NODES_H__

namespace OLS 
{
    // Tags used to identify various tree nodes within the GUI.
    enum FrameTreeNodes {
        NODE_LIGHT_FRAMES = 0x0,
        NODE_DARK_FRAMES = 0x1, 
        NODE_STANDARD_DARK_FRAME_ENTRY = 0x10,
        NODE_STANDARD_LIGHT_FRAME_ENTRY = 0x11
    };
}

#endif