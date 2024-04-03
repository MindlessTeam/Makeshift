// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Util.h"

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <imgui/imgui.h>

namespace MakeshiftEditor
{

	std::string Util::trimTextToFitArea(const std::string& text, float availableSpace, bool reverseTrim)
	{

        ImVec2 ellipsisSize = ImGui::CalcTextSize("...");

        ImVec2 textSize = ImGui::CalcTextSize((text + "...").c_str());

        if (textSize.x > availableSpace) 
        {
            size_t numCharsToShow = 0;
            float accumulatedWidth = 0.0f;
            for (size_t i = 0; i < text.length(); ++i) 
            {
                char currentChar = text[i];
                accumulatedWidth += ImGui::CalcTextSize(&currentChar, &currentChar + 1).x;
                
                if (reverseTrim) 
                {
                    if (accumulatedWidth + ellipsisSize.x > availableSpace) 
                    {
                        break;
                    }
                }
                else 
                {
                    if (accumulatedWidth > availableSpace - ellipsisSize.x) 
                    {
                        break;
                    }
                }
                numCharsToShow++;
            }

            // Trim the text to fit within the available width and append ellipsis
            if (reverseTrim) 
            {
                return "..." + text.substr(text.length() - numCharsToShow, numCharsToShow);
            }
            else 
            {
                return text.substr(0, numCharsToShow) + "...";
            }
        }
        else 
        {
            return text;
        }

	}

    float Util::getRequiredVerticalTextSize(int lines)
    {

        return (((Makeshift::ImGuiRenderer::getFontSize()) + (4 * Makeshift::ImGuiRenderer::getUISizeModifier())) * lines) + (4 * Makeshift::ImGuiRenderer::getUISizeModifier());

    }

}