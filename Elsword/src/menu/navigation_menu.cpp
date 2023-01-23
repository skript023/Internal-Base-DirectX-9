#include <imgui.h>
#include <pointers.hpp>
#include <utility/subprocess.hpp>
#include <menu/navigation_menu.h>


namespace big
{
	bool navigation::nav_button(const std::string_view text)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.f, 0.5f });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0, 5 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 2 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, { 0, 0 });
		bool result = ImGui::Button(text.data(), { ((float)g_pointers->m_resolution->x * 0.15f) - 30, 0 });
		ImGui::PopStyleVar(4);
		ImGui::PopStyleColor(3);

		return result;
	}

	void navigation::navigation_item(std::pair<tabs, navigation_struct>& navItem, int nested)
	{
		const bool curTab = !g_gui_service->get_selected_tab().empty() && g_gui_service->get_selected_tab().size() > nested && navItem.first == g_gui_service->get_selected_tab().at(nested);
		if (curTab)
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.29f, 0.45f, 0.69f, 1.f));

		if (nav_button(navItem.second.name))
			g_gui_service->set_selected(navItem.first);

		if (curTab)
			ImGui::PopStyleColor();

		if (curTab && !navItem.second.sub_nav.empty())
		{
			ImDrawList* dl = ImGui::GetForegroundDrawList();

			for (std::pair<tabs, navigation_struct> item : navItem.second.sub_nav)
			{
				dl->AddRectFilled({ 10.f, ImGui::GetCursorPosY() + 100.f }, { 10.f + 300.f, ImGui::GetCursorPosY() + 100.f + ImGui::CalcTextSize("A").y + ImGui::GetStyle().ItemInnerSpacing.y * 2 }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, .15f + (.075f * nested) }));
				navigation_item(item, nested + 1);
			}
		}

		g_gui_service->increment_nav_size();
	}

	static char username[32] = "unknown";
	static std::once_flag flag;

	void navigation::header()
	{
		ImGui::SetNextWindowSize({ 300.f, 80.f });
		ImGui::SetNextWindowPos({ 10.f, 10.f });
		std::call_once(flag, [] {  strcpy(username, subprocess::check_output("hostname").buf.data()); });

		if (ImGui::Begin("menu_heading", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::BeginGroup();
			ImGui::Text("Welcome");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.172f, 0.380f, 0.909f, 1.f));
			ImGui::Text(username);
			ImGui::PopStyleColor();
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::SetCursorPos({ 300.f - ImGui::CalcTextSize("Unload").x - ImGui::GetStyle().ItemSpacing.x, ImGui::GetStyle().WindowPadding.y / 2 + ImGui::GetStyle().ItemSpacing.y + (ImGui::CalcTextSize("W").y / 2) });
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
			if (nav_button("Unload"))
			{
				g_running = false;
			}
			ImGui::PopStyleColor();
		}
	}

	void navigation::active_view()
	{
		if (g_gui_service->get_selected()->func == nullptr) return;

		static float alpha = 1.f;

		ImGui::SetNextWindowPos({ 300.f + 20.f, 100.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 0.f, 0.f });
		ImGui::SetNextWindowSizeConstraints({ 300.f, 100.f }, { (float)g_pointers->m_resolution->x - 270.f, (float)g_pointers->m_resolution->y - 110.f });
		if (ImGui::Begin("main", nullptr, window_flags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);

			ImGui::PushFont(g_settings->window.font_title);
			ImGui::TextWrapped(g_gui_service->get_selected()->name);
			ImGui::PopFont();

			ImGui::Separator();
			g_gui_service->get_selected()->func();
			ImGui::PopStyleVar();
		}
	}

	void navigation::render_menu() 
	{
		ImGui::SetNextWindowPos({ 10.f, 100.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 300.f, 0.f }, ImGuiCond_Always);

		if (ImGui::Begin("navigation", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			g_gui_service->reset_nav_size();
			for (std::pair<tabs, navigation_struct> navItem : g_gui_service->get_navigation())
			{
				switch (navItem.first)
				{
				case tabs::PLAYER:
				case tabs::DEBUG:
					continue;
				default:
					navigation_item(navItem, 0);
				}
			}

			ImGui::End();
		}
	}
}
