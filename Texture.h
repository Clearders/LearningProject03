//
// Created by 13191 on 2025/11/19.
//

#ifndef LEARNINGPROJECT03_TEXTURE_H
#define LEARNINGPROJECT03_TEXTURE_H
#include "Renderer.h"


class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline unsigned GetRenderer() const { return m_RendererID; }
};


#endif //LEARNINGPROJECT03_TEXTURE_H