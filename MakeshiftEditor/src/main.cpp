// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#define MAKESHIFT_EDITOR
#define MAKESHIFT_IMGUI

#include <Makeshift/Makeshift.hpp>

#include <clientAPI.h>

#include <imgui/imgui.h> 

namespace MakeshiftEditor
{

	class Editor : public Makeshift::Engine
	{

		void init() override
		{

			Client::registerEntities();

		}

		void update() override
		{

			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if(ImGui::MenuItem("New[unimplemented]")) {}
					if(ImGui::MenuItem("Open[unimplemented]")) {}
					if(ImGui::MenuItem("Save[unimplemented]")) {}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Tools"))
				{
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Client"))
				{
					Client::clientMenuItems();
					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}

			Client::renderIMGUI();

			ImGui::ShowDemoWindow();

		}

		void cleanUp() override
		{

		}

	private:

	};

}

int main()
{

	MakeshiftEditor::Editor editor;
	editor.run();

}