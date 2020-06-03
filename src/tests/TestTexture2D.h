#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test {

	class TestTexture2D : public Test
	{
	private:
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<VertexBufferLayout> m_layout;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;

	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}