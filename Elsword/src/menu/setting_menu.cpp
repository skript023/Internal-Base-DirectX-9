#include "imgui.h"
#include <script.hpp>
#include "setting_menu.h"
#include "settings.hpp"

namespace big
{
    void setting_menu::render_menu()
    {
        if (ImGui::Button("Quit"))
        {
            g_running = false;
        }
    }

    void setting_menu::gui_settings()
    {
        static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g_settings->window.color);
        if (ImGui::ColorEdit4("Gui Color##gui_picker", (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
        {
            g_settings->window.color = ImGui::ColorConvertFloat4ToU32(col_gui);
        }
    }
}