// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "EditorWindows/EditorWindow.h"

#include "EditorWindows/General/AboutWindow.h"

#include <Makeshift/Debug/Log.h>
#include <Makeshift/Core/Event.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct ImGuiPayload;

namespace MakeshiftEditor
{

	// Editor
	// ----------------------------------------------
	// Editor base class. Keeps track of all
	// editor windows. Allows for easy integration
	// of client editor windows and provides an 
	// easy interface for Editor Windows to interact
	// with one-another.
	class Editor
	{

	public:
		// Editor::init()
		// ------------------------------------------
		// initializes the Editor
		void init();

		// Editor::run()
		// ------------------------------------------
		// runs all editor functionality and renders
		// all editor windows.
		void run();

	public:
		Makeshift::Event<ImGuiPayload> OnExternalDragDropEvent;

	public:
		// Editor::addEditorWindow()
		// ------------------------------------------
		// Adds an editor window to the list of managed
		// editor windos.
		//
		//Parameters:
		// - menu: the dropdown menu which will show the editor window toggle
		// - window: the window
		void addEditorWindow(const std::string& menu, std::shared_ptr<EditorWindow> window);

		// Editor::getEditorWindow()
		// ------------------------------------------
		//Parameters:
		// - T the type of editor window to return
		// 
		//Returns:
		// a shared_ptr to the editor window or nullptr if not found
		template<typename T>
		std::shared_ptr<T> getEditorWindow()
		{
			DEBUG_TRACE("MakeshiftEditor::Editor::getEditorWindow()")

			T object;
			for (auto entry : m_EditorWindows)
			{
				for (auto window : entry.second)
				{
					if (window->getTitle() == object.getTitle())
					{
						return std::dynamic_pointer_cast<T>(window);
					}
				}
			}
			// Couldn't find the editor window
			return nullptr;
		}

	private:
		void renderMenuBar();
		void renderSideBar();

	private:
		std::unordered_map<std::string, std::vector<std::shared_ptr<EditorWindow>>> m_EditorWindows;

	private:
		AboutWindow m_About;

	// ----------------------------------------------

	public:
		static Editor& getInstance() { return *s_Instance; }

	private:
		static Editor* s_Instance;

	};

}