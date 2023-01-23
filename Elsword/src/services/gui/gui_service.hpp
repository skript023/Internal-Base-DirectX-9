#pragma once
#include "menu/player_menu.h"
#include "menu/player_stats.h"
#include "menu/setting_menu.h"

namespace big
{
	enum class tabs {
		NONE,

		PLAYER_MENU,
		PLAYER_STAT,
		ITEM_MANAGER,

		SETTING,
		GUI_SETTINGS,

		PLAYER,
		DEBUG
	};

	struct navigation_struct
	{
		const char name[32] = "";
		std::function<void()> func = nullptr;
		std::map<tabs, navigation_struct> sub_nav{};
	};

	class gui_service final
	{
		std::vector<tabs> current_tab{};
		bool switched_view = true;

		std::map<tabs, navigation_struct> nav = {
			{tabs::PLAYER_MENU, { "Player", player_menu::render_menu, {
				
			}}},
			{tabs::PLAYER_STAT, { "Player Stat", player_stat::render_menu, {
				
			}}},
			{tabs::ITEM_MANAGER, { "Item Manager", nullptr, {
				
			}}},
			{tabs::SETTING, { "Settings", nullptr, {
				{ tabs::GUI_SETTINGS, { "Menu Settings", setting_menu::gui_settings}},
			}}},
		};
	public:
		gui_service();
		virtual ~gui_service();

		int nav_ctr = 0;

		navigation_struct* get_selected();
		std::vector<tabs>& get_selected_tab();
		bool has_switched_view();
		void set_selected(tabs);
		void set_nav_size(int);
		void increment_nav_size();
		void reset_nav_size();
		std::map<tabs, navigation_struct>& get_navigation();
	};

	inline gui_service* g_gui_service{};
}
