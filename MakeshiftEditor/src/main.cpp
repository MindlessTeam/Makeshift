// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#define MAKESHIFT_EDITOR
#define MAKESHIFT_IMGUI

#include <Makeshift/Makeshift.hpp>

#include <clientAPI.h>

#include <imgui/imgui.h> 

#include "EditorWindows/MaterialCreator.h"
#include "EditorWindows/MeshCreator.h"
#include "EditorWindows/LevelEditor.h"

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
					if (ImGui::MenuItem("Material Creator", nullptr, &m_MaterialCreator.enabled)){}
					if (ImGui::MenuItem("Mesh Creator", nullptr, &m_MeshCreator.enabled)){}
					if (ImGui::MenuItem("Level Editor", nullptr, &m_LevelEditor.enabled)){}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Client"))
				{
					Client::clientMenuItems();
					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}

			m_MaterialCreator.renderIMGUI();
			m_MeshCreator.renderIMGUI();
			m_LevelEditor.renderIMGUI();

			Client::renderIMGUI();

		}

		void cleanUp() override
		{

		}

	private:
		MaterialCreator m_MaterialCreator;
		MeshCreator m_MeshCreator;
		LevelEditor m_LevelEditor;

	};

}

int main()
{

	MakeshiftEditor::Editor editor;
	editor.run();

}