/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "scenenode.h"

namespace scene {

// holds lists of grouped scene nodes
class node_groups {
    // NOTE: during scenario deserialization encountering *.inc file causes creation of a new group on the group stack
    // this allows all nodes listed in this *.inc file to be grouped and potentially modified together by the editor.
private:
    // types
    using node_sequence = std::vector<scene::basic_node *>;

public:
// constructors
    node_groups() = default;
// methods
    // requests creation of a new node group. returns: handle to the group
    group_handle
        begin();
    // indicates creation of current group ended. returns: handle to the parent group or null_handle if group stack is empty
    group_handle
        end();
    // returns current active group, or null_handle if group stack is empty
    group_handle
        handle() const;
    // places provided node in specified group
    void
        register_node( scene::basic_node *Node, scene::group_handle const Group );
    std::pair<node_sequence::iterator, node_sequence::iterator>
        group( scene::group_handle const Group ) {
            auto &group { m_groupmap[ Group ] };
            return { std::begin( group ), std::end( group ) }; }

private:
// types
    using group_map = std::unordered_map<scene::group_handle, node_sequence>;
// methods
    // removes specified group from the group list and group information from the group's nodes
    void
        erase( group_map::const_iterator Group );
    // creates handle for a new group
    group_handle
        create_handle();
// members
    group_map m_groupmap; // map of established node groups
    std::stack<scene::group_handle> m_activegroup; // helper, group to be assigned to newly created nodes
};

extern node_groups Groups;

} // scene

//---------------------------------------------------------------------------
