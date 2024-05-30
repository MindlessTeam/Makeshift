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
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <Makeshift/Resource/ResourceMap.h>

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <GLFW/glfw3.h>

#include "EditorWindows/FileBrowser.h"
#include "EditorWindows/TextureEditor.h"
#include "EditorWindows/LevelMap.h"
#include "EditorWindows/Console.h"

namespace MakeshiftEditor
{

	class Editor : public Makeshift::Engine
	{

		void init() override
		{
			Client::initLog();
			Client::registerEntities();

			glfwSetDropCallback(getDisplay()->getNativeWindow(), dragAndDropCallback);

			//loadLevel("shaderTest_level", false);

		}

		void update() override
		{

			
			ImGui::DockSpaceOverViewport(0U, ImGui::GetWindowViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

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
					if(ImGui::MenuItem("Statistics"))
					{
						m_RenderStatistics = !m_RenderStatistics;
					}
					if (ImGui::MenuItem("Show IMGUI Demo Window"))
					{
						m_RenderImGuiDemo = !m_RenderImGuiDemo;
					}
					if (ImGui::MenuItem("Open Current Location"))
					{

					}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("File Browser"))
					{
						m_FileBrowser.enabled = !m_FileBrowser.enabled;
					}
					if (ImGui::MenuItem("Texture Editor"))
					{
						m_TextureEditor.enabled = !m_TextureEditor.enabled;
					}
					if (ImGui::MenuItem("Level Map"))
					{
						m_LevelMap.enabled = !m_LevelMap.enabled;
					}
					ImGui::EndMenu();
				}
			
				if (ImGui::BeginMenu("Client"))
				{
					Client::clientMenuItems();
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Settings"))
				{
					if (ImGui::MenuItem("Fullscreen"))
					{
						Makeshift::DisplaySettings displaySettings = Makeshift::Engine::getInstance().getDisplay()->getDisplaySettings();
					
						switch (displaySettings.mode)
						{
						case Makeshift::DisplaySettings::WINDOWED:
							displaySettings.mode = Makeshift::DisplaySettings::FULLSCREEN;
							break;
						case Makeshift::DisplaySettings::FULLSCREEN:
							displaySettings.height = Makeshift::Engine::getInstance().getDisplay()->getDisplaySettings().height - 25;
							displaySettings.mode = Makeshift::DisplaySettings::WINDOWED;
							break;
						}
					
						Makeshift::Engine::getInstance().getDisplay()->setDisplaySettings(displaySettings);
					}
					if (ImGui::MenuItem("Double UI"))
					{
						Makeshift::ImGuiRenderer::doubleUISize();
					}
					if (ImGui::MenuItem("Half UI"))
					{
						Makeshift::ImGuiRenderer::halfUISize();
					}
					ImGui::EndMenu();
				}
			
				ImGui::EndMainMenuBar();
			}
			
			//ImGui::End();

			if (m_RenderStatistics)
				renderStatistics();

			if (m_RenderImGuiDemo)
				ImGui::ShowDemoWindow(&m_RenderImGuiDemo);

			m_FileBrowser.renderIMGUI();
			m_TextureEditor.renderIMGUI();
			m_LevelMap.renderIMGUI();
			m_Console.renderIMGUI();

			Client::renderIMGUI();

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) 
			{
				DEBUG_ERROR("OPENGL ERROR: {}", error);
			}

		}

		void cleanUp() override
		{

		}

	private:
		FileBrowser m_FileBrowser;
		TextureEditor m_TextureEditor;
		LevelMap m_LevelMap;
		Console m_Console;

	private:
		bool m_RenderImGuiDemo = false;

		bool m_RenderStatistics = true;
		void renderStatistics()
		{
			ImGui::SetNextWindowBgAlpha(0.2f);
			ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x - 40, ImGui::GetWindowPos().y - 20));

			ImGui::Begin("Statistics", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);
			ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.5f, 1.0f), "FPS: %.2f", (1 / Makeshift::Time::getDeltaTime()));
			ImGui::Text("DeltaTime: %f", Makeshift::Time::getDeltaTime());
			ImGui::Text("Elapsed Time: %.1f s", Makeshift::Time::getElapsed());

			ImGui::End();
		}

	private:
		static void dragAndDropCallback(GLFWwindow* window, int count, const char** paths)
		{
			for (int i = 0; i < count; i++)
			{
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
				{
					ImGui::SetDragDropPayload("EXTERNAL", paths[i], strlen(paths[i]) + 1);
					ImGui::EndDragDropSource();
				}
			}
		}

	};

}

int main()
{

	MakeshiftEditor::Editor editor;
	editor.run();

}