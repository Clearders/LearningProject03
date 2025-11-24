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

void Renderer::Drew(const VertexArray& va, IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
