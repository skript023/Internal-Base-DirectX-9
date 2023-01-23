#pragma once
#include "services/gui/gui_service.hpp"

namespace big
{
	class navigation
	{
		inline static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav;
	public:
		static void render_menu();
		static void header();
		static void active_view();
		static void navigation_item(std::pair<tabs, navigation_struct>& navItem, int nested);
		static bool nav_button(const std::string_view text);
	};
}