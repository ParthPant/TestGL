#pragma once

#include <vector>
#include <string>
#include <functional>

#include "GLFW/glfw3.h"

namespace test {

	class Test 
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime, GLFWwindow *window){}
		virtual void OnRender(){}
		virtual void OnImGuiRender(){}
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.push_back(std::make_pair(name, []() {return new T; }));
		}
	};
}