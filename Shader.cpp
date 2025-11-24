//
// Created by 13191 on 2025/11/18.
//
#include <sstream>
#include "Shader.h"
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include "Renderer.h"

Shader::Shader(const std::string& filepath)
    :m_FilePath(filepath),m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    // 保存返回的 program id 到成员变量，避免后续使用未初始化的 m_RendererID
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    if (m_RendererID == 0)
    {
        std::cerr << "Failed to create shader program from: " << filepath << std::endl;
    }
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name),value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name),value));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
    if (location == -1)
    {
        std::cerr << "Warning: uniform '" << name << "' not found (or program not linked/used)." << std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    if (!stream.is_open())
    {
        // 处理文件打开失败
        std::cerr << "Could not open file: " << filepath << std::endl;
        return { "", "" };
    }

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
            else
            {
                type = ShaderType::NONE; // 遇到未知的shader类型，设置为NONE
            }
        }
        else
        {
            // 只有当type不是NONE时，才写入
            if (type != ShaderType::NONE)
            {
                ss[(int)type] << line << "\n";
            }
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to compile"<<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<< " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


unsigned int Shader::CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
{
    unsigned int program =  glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    // 如果任一 shader 编译失败，清理并返回 0
    if (vs == 0 || fs == 0) {
        if (vs) glDeleteShader(vs);
        if (fs) glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);

    // 检查链接状态
    int linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        int length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, ' ');
        glGetProgramInfoLog(program, length, &length, &message[0]);
        std::cerr << "Failed to link program: " << message << std::endl;

        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
