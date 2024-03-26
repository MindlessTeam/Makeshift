// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ImGuiRenderer.h"

#include "Makeshift/Makeshift.hpp"

#include "Makeshift/Utility/FileSystem.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Makeshift
{

	float ImGuiRenderer::s_FontSizeDefault = 16.0f;
	float ImGuiRenderer::s_UISizeModifier = 1.0f;
	bool ImGuiRenderer::s_ResizeRequested = false;
	bool ImGuiRenderer::s_IsInitialized = false;

	void ImGuiRenderer::initializeImGui()
	{
		DEBUG_TRACE("Makeshift::ImGuiRenderer::initializeImGui()");

		DEBUG_INFO("Initializing ImGui...");

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.Fonts->AddFontFromFileTTF((FileLocations::fontLocation() + "SegUIVar.ttf").c_str(), getFontSize());

		loadFileFromDisk();

		DEBUG_INFO("Applying ImGui style...");

		ImGui::StyleColorsDark();

		ImGui::GetStyle().WindowPadding = ImVec2(4 * s_UISizeModifier, 5 * s_UISizeModifier);
		ImGui::GetStyle().FramePadding = ImVec2(4 * s_UISizeModifier, 4 * s_UISizeModifier);
		ImGui::GetStyle().CellPadding = ImVec2(4 * s_UISizeModifier, 4 * s_UISizeModifier);
		ImGui::GetStyle().ItemSpacing = ImVec2(4 * s_UISizeModifier, 4 * s_UISizeModifier);
		ImGui::GetStyle().ItemInnerSpacing = ImVec2(4 * s_UISizeModifier, 4 * s_UISizeModifier);
		ImGui::GetStyle().TouchExtraPadding = ImVec2(2, 2);
		ImGui::GetStyle().IndentSpacing = 30;
		ImGui::GetStyle().ScrollbarSize = 15;
		ImGui::GetStyle().GrabMinSize = 11;

		ImGui::GetStyle().WindowBorderSize = 1;
		ImGui::GetStyle().ChildBorderSize = 0;
		ImGui::GetStyle().PopupBorderSize = 0;
		ImGui::GetStyle().FrameBorderSize = 0;
		ImGui::GetStyle().TabBorderSize = 0;

		ImGui::GetStyle().WindowRounding = 5;
		ImGui::GetStyle().ChildRounding = 0;
		ImGui::GetStyle().FrameRounding = 2;
		ImGui::GetStyle().PopupRounding = 0;
		ImGui::GetStyle().ScrollbarRounding = 1;
		ImGui::GetStyle().GrabRounding = 2;
		ImGui::GetStyle().LogSliderDeadzone = 2;
		ImGui::GetStyle().TabRounding = 2;

		ImGui::GetStyle().WindowTitleAlign = ImVec2(0, 0.5f);
		ImGui::GetStyle().ButtonTextAlign = ImVec2(0, 0.5f);
		ImGui::GetStyle().SelectableTextAlign = ImVec2(0, 0);

		ImGui::GetStyle().DisplaySafeAreaPadding = ImVec2(3, 1);

		ImVec4* colours = ImGui::GetStyle().Colors;
		colours[ImGuiCol_TextDisabled] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
		colours[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_PopupBg] = ImVec4(0.17f, 0.19f, 0.24f, 1.00f);
		colours[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
		colours[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.35f, 0.44f, 1.00f);
		colours[ImGuiCol_FrameBgHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_TitleBgActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_MenuBarBg] = ImVec4(0.31f, 0.35f, 0.44f, 1.00f);
		colours[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.35f, 0.43f, 1.00f);
		colours[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_SliderGrabActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_Button] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_ButtonHovered] = ImVec4(0.83f, 0.26f, 0.34f, 1.00f);
		colours[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_Header] = ImVec4(0.31f, 0.35f, 0.43f, 1.00f);
		colours[ImGuiCol_HeaderHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_Separator] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colours[ImGuiCol_SeparatorHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_ResizeGrip] = ImVec4(0.31f, 0.35f, 0.44f, 1.00f);
		colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_ResizeGripActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colours[ImGuiCol_Tab] = ImVec4(0.13f / 2, 0.16f / 2, 0.22f / 2, 1.00f);
		colours[ImGuiCol_TabHovered] = ImVec4(0.13f * 2, 0.16f * 2, 0.22f * 2, 1.00f);
		colours[ImGuiCol_TabActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_DockingPreview] = ImVec4(0.13f, 0.16f, 0.22f, 1.00f);
		colours[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		colours[ImGuiCol_NavHighlight] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);


		GLFWwindow* window = Makeshift::Engine::getInstance().getDisplay()->getNativeWindow();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");

	}

	void ImGuiRenderer::prepareFrame()
	{

		if (s_ResizeRequested)
			updateImGuiStyle();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();

		ImGui::NewFrame();

	}

	void ImGuiRenderer::endFrame()
	{

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(Makeshift::Engine::getInstance().getDisplay()->getDisplaySettings().width,
			Makeshift::Engine::getInstance().getDisplay()->getDisplaySettings().height);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			glfwMakeContextCurrent(backup);
		}

		if (!s_IsInitialized)
			s_IsInitialized = true;

	}

	void ImGuiRenderer::cleanUp()
	{
		DEBUG_TRACE("Makeshift::ImGuiRenderer::cleanUp()");

		if (!s_IsInitialized)
			return;

		if(!s_ResizeRequested)
			saveFileToDisk();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiRenderer::updateImGuiStyle()
	{
		cleanUp();
		initializeImGui();

		s_ResizeRequested = false;
		s_IsInitialized = false;
	}

	void ImGuiRenderer::saveFileToDisk()
	{
		if (!s_IsInitialized)
			return;

		std::string modifier = std::to_string(s_UISizeModifier);

		size_t dotPosition = modifier.find('.');
		if (dotPosition != std::string::npos)
		{
			modifier.erase(dotPosition, 1);
		}

		std::string fileName = std::string("imgui_" + modifier + ".ini").c_str();
		ImGui::SaveIniSettingsToDisk(fileName.c_str());
	}

	void ImGuiRenderer::loadFileFromDisk()
	{
		std::string modifier = std::to_string(s_UISizeModifier);

		size_t dotPosition = modifier.find('.');
		if (dotPosition != std::string::npos)
		{
			modifier.erase(dotPosition, 1);
		}

		std::string fileName = std::string("imgui_" + modifier + ".ini").c_str();
		ImGui::LoadIniSettingsFromDisk(fileName.c_str());
	}

	void ImGuiRenderer::doubleUISize()
	{
		saveFileToDisk();
		s_UISizeModifier *= 2;
		s_ResizeRequested = true;
	}

	void ImGuiRenderer::halfUISize()
	{
		saveFileToDisk();
		s_UISizeModifier /= 2;
		s_ResizeRequested = true;
	}

	void ImGuiRenderer::setUISize(float size)
	{
		saveFileToDisk();
		s_UISizeModifier = size;
		s_ResizeRequested = true;
	}

	void ImGuiRenderer::applyModifiersBasedOnMonitorResolution(float width, float height)
	{
		float horizontalScalingFactor = width / 1920;
		float verticalScalingFactor = height / 1080;

		saveFileToDisk();
		s_UISizeModifier = (horizontalScalingFactor + verticalScalingFactor) / 2;
		s_ResizeRequested = true;
	}

}