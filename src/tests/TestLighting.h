#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include <memory>

namespace test {

	class TestLighting : public Test
	{
	private:
		std::unique_ptr<VertexBuffer> m_vb_object;
		std::unique_ptr<VertexBuffer> m_vb_source;
		//std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<VertexBufferLayout> m_layout_object;
		std::unique_ptr<VertexBufferLayout> m_layout_source;
		std::unique_ptr<VertexArray> m_va_object;
		std::unique_ptr<VertexArray> m_va_source;
		std::unique_ptr<Shader> m_shader_object;
		std::unique_ptr<Shader> m_shader_source;
		std::unique_ptr<Texture> m_texture_object;
		std::unique_ptr<Camera> m_Camera;

		glm::mat4 m_proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		glm::mat4 m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		/*std::unique_ptr<glm::vec3> scaleVec;
		std::unique_ptr<glm::vec3> rotateVec;

		float m_rotation = 0.0f;*/

		/*enum class projection{
			ORTHO = 1, PERSP = 0
		};

		projection m_projection = projection::PERSP;*/

		GLFWwindow* m_window;
		float m_lastX;
		float m_lastY;
		float m_deltaTime;

	public:
		TestLighting();
		~TestLighting();

		void OnUpdate(float deltaTime, GLFWwindow *window) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}