// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#define MAKESHIFT_EDITOR
#define MAKESHIFT_IMGUI

#include "Utility/DragDropTypes.h"
#include "Editor.h"

#include "EditorWindows/ResourceEditing/TextureEditor.h"

#include <Makeshift/Makeshift.hpp>

#include <clientAPI.h>

#include <imgui/imgui.h>

#include <GLFW/glfw3.h>

#include <IconsMaterialSymbols.h>

namespace MakeshiftEditor
{

	class Application : public Makeshift::Engine
	{

		void init() override
		{
			Client::initLog();
			Client::registerEntities();

			glfwSetDropCallback(getDisplay()->getNativeWindow(), dragAndDropCallback);

			m_Editor.init();

			m_Editor.addEditorWindow(ICON_MS_DATA_OBJECT " Resources", std::make_shared<TextureEditor>());
		}

		void update() override
		{

			m_Editor.run();

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
		MakeshiftEditor::Editor m_Editor;

	private:
		static void dragAndDropCallback(GLFWwindow* window, int count, const char** paths)
		{
			for (int i = 0; i < count; i++)
			{
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
				{
					ImGui::SetDragDropPayload(MAKESHIFT_PAYLOAD_EXTERNAL, paths[i], strlen(paths[i]) + 1);
					ImGui::EndDragDropSource();
				}
			}
		}

	};

}

int main()
{

	MakeshiftEditor::Application editor;
	editor.run();

}