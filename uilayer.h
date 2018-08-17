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
#include "texture.h"

// GuiLayer -- basic user interface class. draws requested information on top of openGL screen

struct ui_panel {

    struct text_line {

        std::string data;
        glm::vec4 color;

        text_line( std::string const &Data, glm::vec4 const &Color):
            data(Data), color(Color)
        {}
    };

    ui_panel( const int X, const int Y):
        origin_x(X), origin_y(Y)
    {}

    std::vector<text_line> text_lines;
    int origin_x;
    int origin_y;
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
        set_unit( GLint const Textureunit ) { m_textureunit = Textureunit; }
    // potentially processes provided input key. returns: true if the input was processed, false otherwise
    virtual
    bool
        on_key( int const Key, int const Action );
    // updates state of UI elements
    virtual
    void
        update() {}
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
        clear_texts() { m_panels.clear(); }
    void
        push_back( ui_panel *Panel ) { m_panels.emplace_back( Panel ); }

protected:
// members
    static GLFWwindow *m_window;
    static bool m_cursorvisible;

private:
// methods
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
    // prints specified text, using display lists font
    void
        print( std::string const &Text );
    // draws a quad between coordinates x,y and z,w with uv-coordinates spanning 0-1
    void
        quad( glm::vec4 const &Coordinates, glm::vec4 const &Color );
// members
    static GLint m_textureunit;
    static GLuint m_fontbase; // numer DL dla znaków w napisach

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
