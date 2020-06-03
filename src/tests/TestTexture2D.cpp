#include <glad/glad.h>

#include "TestTexture2D.h"
#include "Renderer.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestTexture2D::TestTexture2D()
	{
		float verticies[] = {
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,	  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f
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

		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}
	void TestTexture2D::OnImGuiRender() 
	{
		
	}

}