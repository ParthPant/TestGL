#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test {

	class Test3D : public Test
	{
	private:
		std::unique_ptr<VertexBuffer> m_vb;
		//std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<VertexBufferLayout> m_layout;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;

		glm::mat4 m_proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		glm::mat4 m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		std::unique_ptr<glm::vec3> scaleVec;
		std::unique_ptr<glm::vec3> rotateVec;

		float m_rotation = 0.0f;

		enum class projection{
			ORTHO = 1, PERSP = 0
		};

		projection m_projection = projection::PERSP;

	public:
		Test3D();
		~Test3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}