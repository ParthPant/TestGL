#pragma once

#include "Test.h"
#include "GLFW/glfw3.h"


namespace test {

	class TestClearColor : public Test
	{
	private:
		float m_ClearColor[4];
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime, GLFWwindow *window) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}