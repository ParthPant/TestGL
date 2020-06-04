#include <glad/glad.h>

#include "Test3D.h"
#include "Renderer.h"

#include "imgui/imgui.h"


namespace test {

	Test3D::Test3D()
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
	Test3D::~Test3D()
	{

	}

	void Test3D::OnUpdate(float deltaTime)
	{

	}
	void Test3D::OnRender() 
	{
		m_shader->Bind();
		m_texture->Bind();
		m_va->Bind();

		glm::mat4 model = glm::mat4(1.0f); // basically the model matrix
		model = glm::rotate(model, glm::radians(rotateVec->x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateVec->y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateVec->z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale (model, *scaleVec);

		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 proj;
		if(m_projection == projection::PERSP)
			proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);
		else
			proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);

		glm::mat4 mvp = proj * view * model;

		m_shader->setUniformMat4f("u_MVP", mvp);
		
		Renderer renderer;
		renderer.EnableDepth();
		renderer.Draw(*m_va, 36, *m_shader);
	}
	void Test3D::OnImGuiRender() 
	{
		ImGui::SliderFloat3("Rotate", &rotateVec->x, 0.0f, 360.0f);
		ImGui::SliderFloat3("Scale", &scaleVec->x, 0.0f, 10.0f);

		if(ImGui::RadioButton("Ortho", (int)m_projection == 1)) 
			m_projection = projection::ORTHO;
		else if(ImGui::RadioButton("Persp", (int)m_projection == 0)) 
			m_projection = projection::PERSP;
	}

}