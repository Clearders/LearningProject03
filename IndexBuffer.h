//
// Created by 13191 on 2025/11/1.
//

#ifndef LEARNINGPROJECT03_INDEXBUFFER_H
#define LEARNINGPROJECT03_INDEXBUFFER_H


class IndexBuffer
{
private:
    unsigned int m_RendererID{};
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data,unsigned int count);
    ~IndexBuffer();

    // 只保留 const 版本，行为不修改对象状态
    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};


#endif //LEARNINGPROJECT03_INDEXBUFFER_H