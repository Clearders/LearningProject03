//
// Created by 13191 on 2025/11/1.
//

#ifndef LEARNINGPROJECT03_RENDERER_H
#define LEARNINGPROJECT03_RENDERER_H




    #define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

#include <GL/glew.h>

void GLClearError();
bool GLLogCall(const char* function,const char* file,int line);



#endif //LEARNINGPROJECT03_RENDERER_H