#include <glad/glad.h>

#include "TestLighting.h"
#include "Renderer.h"

#include "imgui/imgui.h"
#include "GLFW/glfw3.h"



namespace test {

	TestLighting::TestLighting()
	{
		float verticies[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		/*unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};*/

		/*rotateVec = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
		scaleVec = std::make_unique<glm::vec3>(1.0f, 1.0f, 1.0f);*/

		m_Camera = std::make_unique<Camera>(0.005f);

		m_vb_object = std::make_unique<VertexBuffer>(verticies, sizeof(verticies));
		//m_ib = std::make_unique<IndexBuffer>(indices, 6);
		m_layout_object = std::make_unique<VertexBufferLayout>();
		m_layout_object->Push<float>(3);
		m_layout_object->Push<float>(3);
		m_va_object = std::make_unique<VertexArray>();
		m_va_object->AddBuffer(*m_vb_object, *m_layout_object);
		m_va_object->Unbind();
		//m_vb_object->Unbind();
	    //m_ib->Unbind();

		m_va_source = std::make_unique<VertexArray>();
		//m_vb_source = std::make_unique<VertexBuffer>();
		m_layout_source = std::make_unique<VertexBufferLayout>();;
		m_layout_source->Push<float>(3);
		m_layout_source->Push<float>(3);
		m_va_source->AddBuffer(*m_vb_object, *m_layout_source);
		m_va_source->Unbind();
		//m_vb_source->Unbind();

		m_shader_object = std::make_unique<Shader>("res/shaders/LightTestObject.shader");
		//m_shader_object->Bind();
		/*m_texture_object = std::make_unique<Texture>("res/textures/wood.png");
		m_texture_object->Bind();
		m_shader_object->setUniform1i("u_Texture", 0);*/
		//m_shader_object->Unbind();
		//m_texture_object->Unbind();

		m_shader_source = std::make_unique<Shader>("res/shaders/LightTestSource.shader");

	}
	TestLighting::~TestLighting()
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void TestLighting::OnUpdate(float deltaTime, GLFWwindow *window)
	{
		m_deltaTime = deltaTime;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->ProcessKeyboardInput(Camera::direction::RIGHT, deltaTime);

		m_window = window;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float xoffset = xpos - m_lastX;
		float yoffset = m_lastY - ypos; // reversed since y-coordinates range from bottom to top
		m_lastX = xpos;
		m_lastY = ypos;

		m_Camera->ProcessMouseInput(xoffset, yoffset, true);

	}

	void TestLighting::OnRender() 
	{
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

		m_shader_object->Bind();
		//m_texture_object->Bind();
		m_va_object->Bind();
		glm::mat4 model = glm::mat4(1.0f); // basically the model matrix
		/*model = glm::rotate(model, glm::radians(rotateVec->x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateVec->y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateVec->z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale (model, *scaleVec);*/

		glm::mat4 view = m_Camera->GetLookAt();

		glm::mat4 proj;
		proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);
		

		m_shader_object->setUniformMat4f("u_projection", proj);
		m_shader_object->setUniformMat4f("u_view", view);
		m_shader_object->setUniformMat4f("u_model", model);
		m_shader_object->setUniformVec3f("u_lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		m_shader_object->setUniformVec3f("u_objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		m_shader_object->setUniformVec3f("u_lightPos", lightPos);
		m_shader_object->setUniformVec3f("u_viewPos", m_Camera->GetPosition());
		
		Renderer renderer;
		renderer.EnableDepth();
		renderer.Draw(*m_va_object, 36, *m_shader_object);

		m_va_object->Unbind();
		m_shader_object->Unbind();
		
		m_va_source->Bind();
		m_shader_source->Bind();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		m_shader_source->setUniformMat4f("u_projection", proj);
		m_shader_source->setUniformMat4f("u_view", view);
		m_shader_source->setUniformMat4f("u_model", model);
		renderer.Draw(*m_va_source, 36, *m_shader_source);
	}
	void TestLighting::OnImGuiRender() 
	{
		
	}

}