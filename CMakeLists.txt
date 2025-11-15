cmake_minimum_required(VERSION 4.0)
project(LearningProject03)

set(CMAKE_CXX_STANDARD 20)
set(GLEW_DEBUG_LIB "C:/Users/13191/.vcpkg-clion/vcpkg/installed/x64-windows-static/lib/glew32.lib")
set(GLFW_DEBUG_LIB "C:/Users/13191/.vcpkg-clion/vcpkg/installed/x64-windows-static/lib/glfw3.lib")
set(GIU_DEBUG_LIB "C:/Users/13191/.vcpkg-clion/vcpkg/installed/x64-windows-static/lib/GlU32.lib")
set(OPENGL_DEBUG_LIB "C:/Users/13191/.vcpkg-clion/vcpkg/installed/x64-windows-static/lib/OpenGL32.lib")


add_executable(LearningProject03 main.cpp
        Renderer.cpp
        Renderer.h
        VertexBuffer.cpp
        VertexBuffer.h
        VertexBuffer.h
        IndexBuffer.cpp
        IndexBuffer.h
        IndexBuffer.h
        VertexArray.cpp
        VertexArray.h
        VertexBufferLayout.h)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(LearningProject03 PRIVATE
        ${GLFW_DEBUG_LIB}
        ${GLEW_DEBUG_LIB}
        ${GIU_DEBUG_LIB}
        ${OPENGL_DEBUG_LIB}
)
