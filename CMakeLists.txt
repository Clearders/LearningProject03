cmake_minimum_required(VERSION 4.0)
project(LearningProject03)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/utf-8)
endif()

# If vcpkg toolchain is used, vcpkg may set variables such as VCPKG_CRT_LINKAGE and VCPKG_LIBRARY_LINKAGE.
# We detect those to choose matching MSVC CRT (/MT vs /MD) and to define GLEW_STATIC if vcpkg provided static libs.

# 诊断输出，便于调试链接类型不一致的问题
if(DEFINED VCPKG_CRT_LINKAGE)
    message(STATUS "VCPKG_CRT_LINKAGE=${VCPKG_CRT_LINKAGE}")
endif()
if(DEFINED VCPKG_LIBRARY_LINKAGE)
    message(STATUS "VCPKG_LIBRARY_LINKAGE=${VCPKG_LIBRARY_LINKAGE}")
endif()
if(DEFINED VCPKG_TARGET_ARCHITECTURE)
    message(STATUS "VCPKG_TARGET_ARCHITECTURE=${VCPKG_TARGET_ARCHITECTURE}")
endif()

# 在 MSVC 下选择合适的运行时（/MT 或 /MD），以避免与 vcpkg 构建的库发生 CRT 冲突（LNK4098）
if (MSVC)
    if (DEFINED VCPKG_CRT_LINKAGE AND VCPKG_CRT_LINKAGE STREQUAL "static")
        message(STATUS "Using static CRT to match vcpkg (setting /MT).")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "MSVC runtime library" FORCE)
    else()
        message(STATUS "Using dynamic CRT (setting /MD).")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "MSVC runtime library" FORCE)
    endif()
endif()

# 列表中避免重复文件名
add_executable(LearningProject03
        main.cpp
        Renderer.cpp
        Renderer.h
        VertexBuffer.cpp
        VertexBuffer.h
        IndexBuffer.cpp
        IndexBuffer.h
        VertexArray.cpp
        VertexArray.h
        Shader.cpp
        Shader.h
        vendor/std_image/std_image.h
        vendor/std_image/std_image.cpp
        Texture.cpp
        Texture.h
        vendor/imgui/imconfig.h
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui.h
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_impl_opengl3.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h
        vendor/imgui/imstb_truetype.h
        vendor/imgui/imgui_impl_opengl3.h
        vendor/imgui/imgui_impl_opengl3_loader.h
        vendor/imgui/imgui_internal.h
        vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_glfw.h
        Test/test.cpp
        Test/test.h
)

find_package(glm CONFIG REQUIRED)

# 如果存在导入目标就直接链接（会自动带上 include 路径）
if (TARGET glm::glm)
    target_link_libraries(LearningProject03 PRIVATE glm::glm)
else()
    # 兼容老式 Find 模块或自定义安装：回退到变量（仅在变量存在时使用）
    if (DEFINED GLM_INCLUDE_DIRS)
        target_include_directories(LearningProject03 PRIVATE ${GLM_INCLUDE_DIRS})
    endif()
    if (DEFINED GLM_LIBRARIES)
        target_link_libraries(LearningProject03 PRIVATE ${GLM_LIBRARIES})
    endif()
endif()

# 优先使用 find_package 提供的包和目标（更可靠，避免手工路径错误）
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
# 尝试使用 glfw3 的 CONFIG 包（vcpkg 通常提供），失败时回退到 FindGLFW
find_package(glfw3 CONFIG)
if (NOT TARGET glfw)
    find_package(GLFW3 REQUIRED) # 备选，某些系统使用这个包名
endif()

# include dirs for GLEW (兼容旧式 Find 模块)
if (TARGET GLEW::GLEW)
    # modern imported target exists
    set(GLEW_TARGET GLEW::GLEW)
else()
    # fallback to variables provided by FindGLEW
    if (DEFINED GLEW_INCLUDE_DIRS)
        target_include_directories(LearningProject03 PRIVATE ${GLEW_INCLUDE_DIRS})
    endif()
    if (DEFINED GLEW_LIBRARIES)
        set(GLEW_TARGET ${GLEW_LIBRARIES})
    endif()
endif()

# 如果 vcpkg 提供的是静态库（VCPKG_LIBRARY_LINKAGE == static），为可执行定义 GLEW_STATIC
# 这样在包含 <GL/glew.h> 前会使用静态导入约定，避免符号导入/导出不一致（LNK4217）
if (DEFINED VCPKG_LIBRARY_LINKAGE AND VCPKG_LIBRARY_LINKAGE STREQUAL "static")
    message(STATUS "vcpkg provides static libraries; defining GLEW_STATIC for target.")
    target_compile_definitions(LearningProject03 PRIVATE GLEW_STATIC)
endif()

# 链接库：优先使用导入目标，否则使用变量
if (DEFINED GLEW_TARGET)
    if (TARGET ${GLEW_TARGET})
        target_link_libraries(LearningProject03 PRIVATE ${GLEW_TARGET})
    else()
        target_link_libraries(LearningProject03 PRIVATE ${GLEW_TARGET})
    endif()
endif()

# 链接 GLFW（导入目标名可能为 glfw 或 glfw3）
if (TARGET glfw3)
    target_link_libraries(LearningProject03 PRIVATE glfw3)
elseif (TARGET glfw)
    target_link_libraries(LearningProject03 PRIVATE glfw)
elseif (TARGET GLFW::GLFW)
    target_link_libraries(LearningProject03 PRIVATE GLFW::GLFW)
endif()

# 链接 OpenGL
if (TARGET OpenGL::GL)
    target_link_libraries(LearningProject03 PRIVATE OpenGL::GL)
elseif (DEFINED OPENGL_gl_LIBRARY)
    target_link_libraries(LearningProject03 PRIVATE ${OPENGL_gl_LIBRARY})
endif()

# 其它可选设置：为调试/发布设置不同的库或开启多线程优化等
