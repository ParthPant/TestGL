#include <glad/glad.h>

#include "TestTexture2D.h"
#include "Renderer.h"

#include "imgui/imgui.h"


namespace test {

	TestTexture2D::TestTexture2D()
	{
		float verticies[] = {
			-100.0f, -100.0f, 0.0f,   0.0f, 0.0f,
			 100.0f, -100.0f, 0.0f,   1.0f, 0.0f,
			 100.0f,  100.0f, 0.0f,	  1.0f, 1.0f,
			-100.0f,  100.0f, 0.0f,   0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

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
		m_texture = std::make_unique<Texture>("res/textures/logo.png");
		m_texture->Bind();
		m_shader->setUniform1i("u_Texture", 0);
		m_shader->Unbind();
		m_texture->Unbind();

		m_proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	}
	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}
	void TestTexture2D::OnRender() 
	{
		m_shader->Bind();
		m_texture->Bind();
		m_va->Bind();

		glm::mat4 mvp = m_proj * m_view * m_model;

		m_view = glm::translate(glm::mat4(1.0f), *viewTrans);
		m_model = glm::translate(glm::mat4(1.0f), *modelTrans);
		//m_proj = glm::translate(glm::mat4(1.0f), *projTrans);

		m_shader->setUniformMat4f("u_MVP", mvp);
		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}
	void TestTexture2D::OnImGuiRender() 
	{
		ImGui::SliderFloat3("Model", &modelTrans->x, 0.0f, 800.0f);
		ImGui::SliderFloat3("View", &viewTrans->x, 0.0f, 800.0f);
		//ImGui::SliderFloat3("Projection", &projTrans->x, 0.0f, 800.0f);
	}

}