#pragma once

#include <imgui/imgui.h>

#include <Makeshift/Graphics/ImGuiRenderer.h>

namespace MakeshiftEditor
{

	struct Style
	{

		static ImVec4 LighterAccent() {
			return ImVec4(1.00f, 1.00f, 1.00f, 0.28f);
		}

		static ImVec4 LightAccent() {
			return ImVec4(1.00f, 1.00f, 1.00f, 0.14f);
		}

		static ImVec4 DarkAccent() {
			return ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		}

		static ImVec4 DarkOverlay() {
			return ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		}

		static float InternalWindowPaddingAxis() {
			return 10 * Makeshift::ImGuiRenderer::getUISizeModifier();
		}

		static ImVec2 InternalWindowPadding() {
			return ImVec2(InternalWindowPaddingAxis(), InternalWindowPaddingAxis());
		}

		static float ItemSpacing(){
			return 4 * Makeshift::ImGuiRenderer::getUISizeModifier();
		}

		static float ItemSpacingWide() {
			return 10 * Makeshift::ImGuiRenderer::getUISizeModifier();
		}

		static float HeaderIndent() {
			return 20 * Makeshift::ImGuiRenderer::getUISizeModifier();
		}

	};

}