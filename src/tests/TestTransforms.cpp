#include <glad/glad.h>

#include "TestTransforms.h"
#include "Renderer.h"

#include "imgui/imgui.h"


namespace test {

	TestTransforms::TestTransforms()
	{
		float verticies[] = {
			-0.5f,  -0.5f,  0.0f,   0.0f, 0.0f,
			 0.5f,  -0.5f,  0.0f,   1.0f, 0.0f,
			 0.5f,   0.5f,  0.0f,   1.0f, 1.0f,
			-0.5f,   0.5f,  0.0f,   0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		rotateVec = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
		scaleVec = std::make_unique<glm::vec3>(1.0f, 1.0f, 1.0f);

		m_vb = std::make_unique<VertexBuffer>(verticies, sizeof(verticies));
		m_ib = std::make_unique<IndexBuffer>(indices, 6);
		m_layout = std::make_unique<VertexBufferLayout>();
		m_layout->Push<float>(3);
		m_layout->Push<float>(2);
		m_va = std::make_unique<VertexArray>();
		m_va->AddBuffer(*m_vb, *m_layout);
		m_va->Unbind();
		m_vb->Unbind();
	    m_ib->Unbind();

		m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_shader->Bind();
		m_texture = std::make_unique<Texture>("res/textures/wood.png");
		m_texture->Bind();
		m_shader->setUniform1i("u_Texture", 0);
		m_shader->Unbind();
		m_texture->Unbind();

	}
	TestTransforms::~TestTransforms()
	{

	}

	void TestTransforms::OnUpdate(float deltaTime, GLFWwindow *window)
	{

	}
	void TestTransforms::OnRender() 
	{
		m_shader->Bind();
		m_texture->Bind();
		m_va->Bind();

		glm::mat4 transform = glm::mat4(1.0f); // basically the model matrix
		transform = glm::rotate(transform, glm::radians(rotateVec->x), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotateVec->y), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotateVec->z), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, *scaleVec);

		glm::mat4 mvp = transform;

		m_shader->setUniformMat4f("u_MVP", mvp);
		
		Renderer renderer;
		//renderer.EnableDepth();
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}
	void TestTransforms::OnImGuiRender() 
	{
		ImGui::SliderFloat3("Rotate", &rotateVec->x, 0.0f, 360.0f);
		ImGui::SliderFloat3("Scale", &scaleVec->x, 0.0f, 10.0f);
	}

}