#include <glad/glad.h>

#include "TestCamera.h"
#include "Renderer.h"

#include "imgui/imgui.h"

namespace test {

	TestCamera::TestCamera()
	{
		float verticies[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		/*unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};*/

		m_Camera = std::make_unique<Camera>(0.01f);

		rotateVec = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
		scaleVec = std::make_unique<glm::vec3>(1.0f, 1.0f, 1.0f);

		m_vb = std::make_unique<VertexBuffer>(verticies, sizeof(verticies));
		//m_ib = std::make_unique<IndexBuffer>(indices, 6);
		m_layout = std::make_unique<VertexBufferLayout>();
		m_layout->Push<float>(3);
		m_layout->Push<float>(2);
		m_va = std::make_unique<VertexArray>();
		m_va->AddBuffer(*m_vb, *m_layout);
		m_va->Unbind();
		m_vb->Unbind();
	    //m_ib->Unbind();

		m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_shader->Bind();
		m_texture = std::make_unique<Texture>("res/textures/wood.png");
		m_texture->Bind();
		m_shader->setUniform1i("u_Texture", 0);
		m_shader->Unbind();
		m_texture->Unbind();

	}
	TestCamera::~TestCamera()
	{
		/*glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);*/
	}

	void TestCamera::OnUpdate(float deltaTime, GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::RIGHT, deltaTime);

		m_window = window;

		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float lastX = 400, lastY = 300;

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
		lastX = xpos;
		lastY = ypos;

		m_Camera->ProcessMouseInput(xoffset, yoffset, true);
	}

	void TestCamera::OnRender() 
	{
		m_shader->Bind();
		m_texture->Bind();
		m_va->Bind();

		

		glm::mat4 model = glm::mat4(1.0f); // basically the model matrix
		glm::mat4 view = m_Camera->GetLookAt();

		glm::mat4 proj;
		if (m_projection == projection::PERSP)
			proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);
		else
			proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (int i = 0; i < 10; i++) {
			model = glm::rotate(model, glm::radians((float)9*i), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians((float)9*i), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians((float)9*i), glm::vec3(0.0f, 0.0f, 1.0f));
			
			model = glm::translate(model, cubePositions[i]);

			glm::mat4 mvp = proj * view * model;

			m_shader->setUniformMat4f("u_MVP", mvp);

			Renderer renderer;
			renderer.EnableDepth();
			renderer.Draw(*m_va, 36, *m_shader);
		}
	}
	void TestCamera::OnImGuiRender() 
	{
	}

}