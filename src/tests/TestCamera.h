#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test {

	class TestCamera : public Test
	{
	private:
		std::unique_ptr<VertexBuffer> m_vb;
		//std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<VertexBufferLayout> m_layout;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<Camera> m_Camera;

		glm::mat4 m_proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		glm::mat4 m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.0f));
		glm::mat4 m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		std::unique_ptr<glm::vec3> scaleVec;
		std::unique_ptr<glm::vec3> rotateVec;

		GLFWwindow* m_window;

		float m_rotation = 0.0f;

		enum class projection{
			ORTHO = 1, PERSP = 0
		};

		projection m_projection = projection::PERSP;


	public:
		TestCamera();
		~TestCamera();

		void OnUpdate(float deltaTime, GLFWwindow *window) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}