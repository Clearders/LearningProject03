//
// Created by 13191 on 2025/11/1.
//

#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function,const char* file,int line)
{
    while (const GLenum error = glGetError())
    {
        std::cout << "OpenGL Error: " << error << ":" << function << ":" << file << ":" << line << std::endl;
        return false;
    }
    return true;
}