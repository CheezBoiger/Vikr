//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MANUAL_COMMANDS_HPP
#define __VIKR_MANUAL_COMMANDS_HPP


#include <vikr/renderer/command/render_command.hpp>


namespace vikr {

/*
  ATTENTION: This is a list of all commands that will execute according to 
             What the programmer wishes to execute. Sometimes the user may
             want to override and manually handle commands for the Renderer 
             for better performance! To compensate this, we allow manual 
             commands that should be used ONLY IF YOU KNOW WHAT YOU ARE DOING!
             Overriding for manual commands is rather difficult, so be sure you
             understand computer graphics APIs before handling this kind of stuff.

*/


class SetVertexArrayCommand : public RenderCommand {
public:
  
};


class SetVertexBufferCommand : public RenderCommand {
public:

};


class SetTextureCommand : public RenderCommand {
public:

};


class DrawArraysCommand : public RenderCommand {
public:
};


class DrawElementsCommand : public RenderCommand {
public:

};



} // vikr
#endif // __VIKR_MANUAL_COMMANDS_HPP