#include "imgui.h"
#include <script.hpp>
#include "player_menu.h"
#include "settings.hpp"

namespace big
{
	void player_menu::render_menu()
	{
        auto end = std::chrono::system_clock::now();
        std::time_t date = std::chrono::system_clock::to_time_t(end);

        ImGui::Text("%s", std::ctime(&date));

        ImGui::BeginGroup();

        ImGui::Checkbox("Infinite Psychic Gauge", &g_settings->self.infinite_psychic);
        ImGui::Checkbox("SAS No Cooldown", &g_settings->self.no_sas_cooldown);
        ImGui::Checkbox("Infinite SAS Duration", &g_settings->self.infinite_sas_duration);

        ImGui::EndGroup();

        ImGui::SameLine(240.f);

        ImGui::BeginGroup();

        ImGui::Checkbox("No Item Use Cooldown", &g_settings->self.no_items_cooldown);
        ImGui::Checkbox("Infinite Battle Point", &g_settings->self.infinite_battle_point);
        ImGui::Checkbox("Infinite Credits", &g_settings->self.infinite_credits);

        ImGui::EndGroup();

        ImGui::SameLine(480.f);

        ImGui::BeginGroup();

        ImGui::Checkbox("Infinite Brain Drive", &g_settings->self.infinite_brain_dive);
        ImGui::Checkbox("Instant Brain Field", &g_settings->self.instant_brain_field);
        ImGui::Checkbox("Infinite Health", &g_settings->self.infinite_health);

        ImGui::EndGroup();

        if (ImGui::Button("Enter Brain Drive"))
        {

        }

        ImGui::PushItemWidth(200.f);

        //ImGui::SliderFloat("EXP Multiplier", player::player_exp_multiplier(), 1.0f, 1000.f);

        ImGui::Combo("Skill Slot 1", &g_settings->skill.slot_1, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 2", &g_settings->skill.slot_2, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 3", &g_settings->skill.slot_3, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 4", &g_settings->skill.slot_4, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 5", &g_settings->skill.slot_5, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 6", &g_settings->skill.slot_6, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 7", &g_settings->skill.slot_7, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::Combo("Skill Slot 8", &g_settings->skill.slot_8, skill_list, IM_ARRAYSIZE(skill_list));

        ImGui::PopItemWidth();
	}
}