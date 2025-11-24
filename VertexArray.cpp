//
// Created by 13191 on 2025/11/11.
//

#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1,&m_RendererID));
}

VertexArray::~VertexArray()
{
    // 用 GLCall 包裹以便捕获 GL 错误
    GLCall(glDeleteVertexArrays(1,&m_RendererID));
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    // 先绑定当前对象的 VAO，以保证后续顶点属性设置作用于本 VAO
    GLCall(glBindVertexArray(m_RendererID));

    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(static_cast<uintptr_t>(offset))));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
