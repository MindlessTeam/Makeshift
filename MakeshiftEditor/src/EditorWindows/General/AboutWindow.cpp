// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "AboutWindow.h"

#include "UI/Elements.h"

#include <Makeshift/Version.h>

#include <imgui/imgui.h>

namespace MakeshiftEditor
{


	void AboutWindow::renderIMGUI()
	{

		if (!m_Enabled)
			return;

		ImGui::Begin("About", &m_Enabled);

		Elements::CenteredText("Makeshift Engine");

		ImGui::Text("Developed by Aaron Kerker");

		Version version;
		ImGui::Text("Version %d, %d, %d", version.major, version.minor, version.patch);

		ImGui::Separator();

		ImGui::Text("Third Party Libraries:");

		ImGui::BulletText("Premake");
		ImGui::BulletText("glad");
		ImGui::BulletText("GLFW");
		ImGui::BulletText("glm");
		ImGui::BulletText("imgui");
		ImGui::BulletText("jsoncpp");
		ImGui::BulletText("spdlog");
		ImGui::BulletText("stb");
		ImGui::BulletText("tiny_obj_loader.h");

		ImGui::Separator();

		ImGui::Text("Additional:");
		
		ImGui::BulletText("Segoe UI");
		ImGui::BulletText("Material Symbols by Google");

		ImGui::Separator();

		ImGui::Text("Thank you very much for using Makeshift!");

		ImGui::End();

	}

}