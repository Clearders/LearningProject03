#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3_loader.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

int main()
{
    GLFWwindow* window;



    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 810, "Hello World", nullptr, nullptr);



    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(4);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    {
        float positions[] = {
            0.0f,  0.0f,  0.0f, 0.0f,
            1.0f,  0.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f,
            0.0f,  1.0f,  0.0f, 1.0f
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.PushFloat(2);
        layout.PushFloat(2);
        va.AddBuffer(vb,layout);

        IndexBuffer ib(indices,6);

        int windowWidth = 1080;
        int windowHeight = 810;
        glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth,  0.0f,(float)windowHeight, -1.0f, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);


        Shader shader("Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

        Texture texture("textures/test.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture",0);


        va.Unbind();
        shader.UnBind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui_ImplGlfw_InitForOpenGL(window, true);

        glm::vec3 translationA(200.0f,200.0f,0.0f);
        glm::vec3 translationB(400.0f,200.0f,0.0f);

        glm::vec3 scaleVec(96.0f, 140.0f, 1.0f);

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            GLCall(glClearColor(0.2f,0.25f,0.3f,1.0f));

            //new ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f),translationA)*
                                  glm::scale(glm::mat4(1.0f),scaleVec);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP",mvp);

                renderer.Drew(va,ib,shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f),translationB)*
                                  glm::scale(glm::mat4(1.0f),scaleVec);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP",mvp);

                renderer.Drew(va,ib,shader);
            }

            if (r > 1.0f)
            {
                increment = -0.05f;
            }else if (r < 0.0f)
            {
                increment =  0.05f;
            }
            r += increment;

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            }

            //Render ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
