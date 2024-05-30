// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Input.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

namespace Makeshift
{

	void Input::init()
	{

		GLFWwindow* window = glfwGetCurrentContext();

		glfwSetKeyCallback(window, keyCallback);

	}

	void Input::pollInput()
	{
		DEBUG_TRACE("Makeshift::Input::pollInput()");

		glfwPollEvents();
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		// Handle IMGUI
		ImGuiIO& io = ImGui::GetIO();
		if (action == GLFW_PRESS)
		{
			io.KeysDown[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			io.KeysDown[key] = false;
		}

		io.KeyCtrl = (mods & GLFW_MOD_CONTROL) != 0;
		io.KeyShift = (mods & GLFW_MOD_SHIFT) != 0;
		io.KeyAlt = (mods & GLFW_MOD_ALT) != 0;
		io.KeySuper = (mods & GLFW_MOD_SUPER) != 0;

	}

}