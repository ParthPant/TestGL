#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to creste GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    {//Scope to run destructors before glfwterminate
        float vertices[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,0.0f,
             50.0f, -50.0f, 0.0f, 1.0f,0.0f,
             50.0f,  50.0f, 0.0f, 1.0f,1.0f,
            -50.0f,  50.0f, 0.0f, 0.0f,1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray VA;
        VertexBuffer VB(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        VA.AddBuffer(VB, layout);
        IndexBuffer IB(indices, 6);
        VA.Unbind();
        VB.Unbind();
        IB.Unbind();

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        Texture texture("res/textures/logo.png");
        texture.Bind();
        shader.setUniform1i("u_Texture", 0);
        shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translation1(0, 0, 0);
        glm::vec3 translation2(200, 0, 0);

        while (!glfwWindowShouldClose(window)) {
            processInput(window);

            renderer.Clear();

            shader.Bind();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation1);
                glm::mat4 mvp1 = proj * view * model;

                
                shader.setUniformMat4f("u_MVP", mvp1);

                renderer.Draw(VA, IB, shader);
            }
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
                glm::mat4 mvp2 = proj * view * model;

                shader.setUniformMat4f("u_MVP", mvp2);

                renderer.Draw(VA, IB, shader);

            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("Hello, world!");                          

                ImGui::SliderFloat3("Translation1", &translation1.x, 0.0f, 800.0f);
                ImGui::SliderFloat3("Translation2", &translation2.x, 0.0f, 800.0f);          
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    //ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}