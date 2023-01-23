#pragma once
#include "common.hpp"
#include <imgui.h>

namespace big
{
	class renderer
	{
	public:
		explicit renderer();
		~renderer();

		bool m_init = false;
		bool init(IDirect3DDevice9* swapchain);
		void imgui_init(IDirect3DDevice9* device);

		void on_present();

		void pre_reset();
		void post_reset();
		void merge_icon_with_latest_font(float font_size, bool FontDataOwnedByAtlas = false);

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	public:
		ImFont* m_font = nullptr;
		ImFont* m_monospace_font = nullptr;

		HWND m_window = NULL;
	private:
		LPDIRECT3DDEVICE9 m_d3d_device = nullptr;
	};

	inline renderer *g_renderer{};
}
