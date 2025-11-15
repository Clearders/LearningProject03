//
// Created by 13191 on 2025/11/1.
//

#ifndef LEARNINGPROJECT03_VERTEXBUFFER_H
#define LEARNINGPROJECT03_VERTEXBUFFER_H


class VertexBuffer
{
    private:
    unsigned int m_RendererID;

    public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};


#endif //LEARNINGPROJECT03_VERTEXBUFFER_H