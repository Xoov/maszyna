﻿/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <string>
#include "Texture.h"

// GuiLayer -- basic user interface class. draws requested information on top of openGL screen

class ui_panel {

public:
// constructor
    ui_panel( std::string const &Identifier, bool const Isopen );
// methods
    virtual void update() {};
    virtual void render();
    // temporary  access
// types
    struct text_line {

        std::string data;
        glm::vec4 color;

        text_line( std::string const &Data, glm::vec4 const &Color)
            : data(Data), color(Color)
        {}
    };
// members
    std::string title;
    bool is_open;
    glm::ivec2 size { -1, -1 };
    glm::ivec2 size_min { -1, -1 };
    glm::ivec2 size_max { -1, -1 };
    std::vector<text_line> text_lines;

protected:
// members
    std::string name;
};

class ui_layer {

public:
// constructors
    ui_layer() = default;
// destructor
    virtual ~ui_layer();

// methods
    static
    bool
        init( GLFWwindow *Window );
    // assign texturing hardware unit
    static
    void
        set_unit( GLint const Textureunit ) { m_textureunit = GL_TEXTURE0 + Textureunit; }
    static
    void
        shutdown();
    // potentially processes provided input key. returns: true if the input was processed, false otherwise
    bool
        on_key( int const Key, int const Scancode, int const Action, int const Mods );
    // potentially processes provided input character. returns: true if the input was processed, false otherwise
    bool
        on_char( unsigned int const Char );
    // potentially processes provided mouse movement. returns: true if the input was processed, false otherwise
    bool
        on_cursor_pos( double const Horizontal, double const Vertical );
    // potentially processes provided mouse button. returns: true if the input was processed, false otherwise
    bool
        on_mouse_button( int const Button, int const Action, int const Mods );
    // potentially processes provided mouse scroll event. returns: true if the input was processed, false otherwise
    bool
        on_scroll( double const Xoffset, double const Yoffset );
    // updates state of UI elements
    virtual
    void
        update();
	// draws requested UI elements
	void
        render();
    //
    static
    void
        set_cursor( int const Mode );
	// stores operation progress
	void
        set_progress( float const Progress = 0.0f, float const Subtaskprogress = 0.0f );
    void
        set_progress( std::string const &Text ) { m_progresstext = Text; }
	// sets the ui background texture, if any
	void
        set_background( std::string const &Filename = "" );
    void
        set_texture( GLuint Texture = 0 ) { m_texture = Texture; }
    void
        set_tooltip( std::string const &Tooltip ) { m_tooltip = Tooltip; }
    void
        clear_panels() { m_panels.clear(); }
    void
        push_back( ui_panel *Panel ) { m_panels.emplace_back( Panel ); }

protected:
// members
    static GLFWwindow *m_window;
    static ImGuiIO *m_imguiio;
    static bool m_cursorvisible;

private:
// methods
    static
    void
        init_colors();
    // render() subclass details
    virtual
    void
        render_() {};
    // draws background quad with specified earlier texture
    void
        render_background();
    void
        render_texture();
    // draws a progress bar in defined earlier state
    void
        render_progress();
    void
        render_panels();
    void
        render_tooltip();
    // input methods subclass details
    virtual
    bool
        on_key_( int const Key, int const Scancode, int const Action, int const Mods ) { return false; }
    virtual
    bool
        on_char_( unsigned int const Char ) { return false; }
    virtual
    bool
        on_cursor_pos_( double const Horizontal, double const Vertical ) { return false; }
    virtual
    bool
        on_mouse_button_( int const Button, int const Action, int const Mods ) { return false; }
    virtual
    bool
        on_scroll_( double const Xoffset, double const Yoffset ) { return false; }
    
// members
    static GLint m_textureunit;

    // progress bar config. TODO: put these together into an object
    float m_progress { 0.0f }; // percentage of filled progres bar, to indicate lengthy operations.
    float m_subtaskprogress{ 0.0f }; // percentage of filled progres bar, to indicate lengthy operations.
    std::string m_progresstext; // label placed over the progress bar
    bool m_progressbottom { true }; // location of the progress bar

    texture_handle m_background { null_handle }; // path to texture used as the background. size depends on mAspect.
    GLuint m_texture { 0 };
    std::vector<ui_panel *> m_panels;
    std::string m_tooltip;
};
