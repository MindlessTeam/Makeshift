// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ImGuiRenderer.h"

#include "Makeshift/Makeshift.hpp"

#include "Makeshift/Utility/FileSystem.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "Makeshift/Utility/MaterialIcons.h"

#include <IconsMaterialSymbols.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Makeshift
{

	float ImGuiRenderer::s_FontSizeDefault = 16.0f;
	float ImGuiRenderer::s_IconFontSizeDefault = 20.0f;
	float ImGuiRenderer::s_UISizeModifier = 1.0f;
	bool ImGuiRenderer::s_ResizeRequested = false;
	bool ImGuiRenderer::s_IsInitialized = false;

	ImFont* ImGuiRenderer::s_IconFont;

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

		
		ImFontConfig fontConfig;
		io.Fonts->AddFontFromFileTTF((FileLocations::fontLocation() + "SegUIVar.ttf").c_str(), getFontSize(), &fontConfig, io.Fonts->GetGlyphRangesDefault());
		
		static const ImWchar glyphRanges[] =
		{
			ICON_MIN_MS, ICON_MAX_16_MS, 0
		};
		fontConfig.OversampleH = 3;
		fontConfig.OversampleV = 3;
		fontConfig.PixelSnapH = true;
		fontConfig.MergeMode = true;
		fontConfig.GlyphMinAdvanceX = getIconFontSize();
		fontConfig.GlyphOffset = ImVec2(0, 4 * getUISizeModifier());
		fontConfig.GlyphExtraSpacing = ImVec2(0, 5);
		io.Fonts->AddFontFromFileTTF((FileLocations::fontLocation() + FONT_ICON_FILE_NAME_MSR).c_str(), getIconFontSize(), &fontConfig, glyphRanges);
		// To be able to use Icons in normal text as well as in enlarged
		// form for buttons, we need to add the icon font twice, once
		// merged with the normal UI-Font and once as a seperate font that
		// can be enabled whenever necessary. This is quite inefficient,
		// but it works and I don't really see a reason we would need to
		// change this.


		fontConfig.GlyphMinAdvanceX = getIconFontSize();
		fontConfig.GlyphOffset = ImVec2(0, 0);
		fontConfig.MergeMode = false;
		s_IconFont = io.Fonts->AddFontFromFileTTF((FileLocations::fontLocation() + FONT_ICON_FILE_NAME_MSR).c_str(), getIconFontSize(), &fontConfig, glyphRanges);

		loadFileFromDisk();

		DEBUG_INFO("Applying ImGui style...");

		ImGui::StyleColorsDark();

		ImGui::GetStyle().WindowPadding = ImVec2(0, 0);
		ImGui::GetStyle().FramePadding = ImVec2(5 * getUISizeModifier(), 5*getUISizeModifier());
		ImGui::GetStyle().CellPadding = ImVec2(0, 0);
		ImGui::GetStyle().ItemSpacing = ImVec2(0, 0);
		ImGui::GetStyle().ItemInnerSpacing = ImVec2(5 * getUISizeModifier(), 5 * getUISizeModifier());
		ImGui::GetStyle().TouchExtraPadding = ImVec2(0, 0);
		ImGui::GetStyle().IndentSpacing = 30;
		ImGui::GetStyle().ScrollbarSize = 15;
		ImGui::GetStyle().GrabMinSize = 11;

		ImGui::GetStyle().WindowBorderSize = 1;
		ImGui::GetStyle().ChildBorderSize = 0;
		ImGui::GetStyle().PopupBorderSize = 1;
		ImGui::GetStyle().FrameBorderSize = 0;
		ImGui::GetStyle().TabBorderSize = 1;

		ImGui::GetStyle().WindowRounding = 5;
		ImGui::GetStyle().ChildRounding = 5;
		ImGui::GetStyle().FrameRounding = 1;
		ImGui::GetStyle().PopupRounding = 2;
		ImGui::GetStyle().ScrollbarRounding = 1;
		ImGui::GetStyle().GrabRounding = 2;
		ImGui::GetStyle().LogSliderDeadzone = 2;
		ImGui::GetStyle().TabRounding = 2;

		ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);
		ImGui::GetStyle().ButtonTextAlign = ImVec2(0.5f, 0.5f);
		ImGui::GetStyle().SelectableTextAlign = ImVec2(0, 0);

		ImGui::GetStyle().DisplaySafeAreaPadding = ImVec2(3, 1);

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 0.98f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.14f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.30f, 0.39f, 0.49f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.30f, 0.39f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.14f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.30f, 0.39f, 0.49f);
		colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.14f);
		colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.30f, 0.39f, 0.49f);
		colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.49f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.96f, 0.30f, 0.39f, 0.49f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.96f, 0.30f, 0.39f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.39f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.30f, 0.39f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(1.00f, 0.30f, 0.39f, 0.49f);
		colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.30f, 0.39f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.30f, 0.39f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(1.00f, 0.30f, 0.39f, 0.49f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.31f);
		colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 1.00f, 1.00f, 0.49f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.38f, 0.35f, 0.49f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);




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