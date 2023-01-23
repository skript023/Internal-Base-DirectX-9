#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "vmt_hook.hpp"

namespace big
{
	struct hooks
	{
		static void* convert_thread_to_fiber(void* param);

		static constexpr auto d3d9_endscene = 42;
		static constexpr auto d3d9_reset = 16;
		static HRESULT APIENTRY endscene(IDirect3DDevice9* _this);
		static HRESULT APIENTRY on_reset(IDirect3DDevice9* _this, D3DPRESENT_PARAMETERS* param);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();
	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		WNDPROC m_og_wndproc;

		detour_hook m_end_scene_hook;
		detour_hook m_on_reset_hook;
		detour_hook m_set_cursor_pos_hook;
	};

	inline hooking* g_hooking{};
}
