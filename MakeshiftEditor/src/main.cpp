// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#define MAKESHIFT_EDITOR
#define MAKESHIFT_IMGUI

#include <Makeshift/Makeshift.hpp>

#include "EditorWindows/Explorer.h"
#include "EditorWindows/ResourceViewer.h"
#include "EditorWindows/LevelViewer.h"

namespace MakeshiftEditor
{

	class Editor : public Makeshift::Engine
	{

		void init() override
		{

		}

		void update() override
		{
			m_Explorer.renderIMGUI();
			m_ResourceViewer.renderIMGUI();
			m_LevelViewer.renderIMGUI();
		}

		void cleanUp() override
		{

		}

	private:
		Explorer m_Explorer;
		ResourceViewer m_ResourceViewer;
		LevelViewer m_LevelViewer;

		static bool s_Explorer;
		static bool s_ResourceViewer;

	};

}

int main()
{

	MakeshiftEditor::Editor editor;
	editor.run();

}