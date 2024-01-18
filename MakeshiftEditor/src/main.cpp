// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#define MAKESHIFT_EDITOR
#define MAKESHIFT_IMGUI

#include <Makeshift/Makeshift.hpp>
#include <Makeshift/Level/Level.h>

#include <clientAPI.h>

#include <imgui/imgui.h> 

#include <Makeshift/Resource/ResourceMap.h>

namespace MakeshiftEditor
{

	class Editor : public Makeshift::Engine
	{

		void init() override
		{
			Client::initLog();
			Client::registerEntities();


			loadLevel("shaderTest_level", false);


		}

		void update() override
		{

			if (!bla)
			{
				bla = true;
			}

			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if(ImGui::MenuItem("New[unimplemented]")) {}
					if(ImGui::MenuItem("Open[unimplemented]")) {}
					if(ImGui::MenuItem("Save[unimplemented]")) {}
			
					ImGui::EndMenu();
				}
			
				if (ImGui::BeginMenu("Debug"))
				{
					if (ImGui::MenuItem("Wireframe"))
					{
						Engine::getInstance().getDisplay()->switchPolygonMode();
					}

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
			
			ImGui::Begin("ResourceMappyOppy");
			
			for (auto resource : getResourceMap()->getResources())
			{
			
				ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), resource.first.c_str());
				ImGui::Text("Usage Count: %d", resource.second.first);
			
				if (ImGui::CollapsingHeader(std::string(resource.first + "Data").c_str()))
				{
					resource.second.second->renderIMGUI();
				}
			
				ImGui::Separator();
			
			}
			
			ImGui::End();
			
			Client::renderIMGUI();
			
			ImGui::ShowDemoWindow();

		}

		void cleanUp() override
		{

		}

	private:
		bool bla = false;

	};

}

int main()
{

	MakeshiftEditor::Editor editor;
	editor.run();

}