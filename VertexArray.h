//
// Created by 13191 on 2025/11/11.
//

#ifndef LEARNINGPROJECT03_VERTEXARRAY_H
#define LEARNINGPROJECT03_VERTEXARRAY_H
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
    private:
        unsigned int m_RendererID;
    public:
        VertexArray();
        ~VertexArray();


        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);


    void Bind() const;
    void Unbind() const;

};


#endif //LEARNINGPROJECT03_VERTEXARRAY_H