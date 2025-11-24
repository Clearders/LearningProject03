//
// Created by 13191 on 2025/11/1.
//

#ifndef LEARNINGPROJECT03_RENDERER_H
#define LEARNINGPROJECT03_RENDERER_H


#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function,const char* file,int line);


class Renderer
{
public:
    void Drew(const VertexArray& va,IndexBuffer& ib,const Shader& shader) const;
};


#endif //LEARNINGPROJECT03_RENDERER_H