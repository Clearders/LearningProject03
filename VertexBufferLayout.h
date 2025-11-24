//
// Created by 13191 on 2025/11/11.
//

#ifndef LEARNINGPROJECT03_VERTEXBUFFERLAYOUT_H
#define LEARNINGPROJECT03_VERTEXBUFFERLAYOUT_H
#include <vector>
#include <GL/glew.h>

#include "Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{

    private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout()
        :m_Stride(0){}

    void PushFloat(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, static_cast<unsigned int>(count), GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void PushUnsignedInt(int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, static_cast<unsigned int>(count), GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void PushUnsignedByte(int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, static_cast<unsigned int>(count), GL_TRUE }); // 通常字节类型会归一化
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const{return m_Stride;}
};

#endif //LEARNINGPROJECT03_VERTEXBUFFERLAYOUT_H