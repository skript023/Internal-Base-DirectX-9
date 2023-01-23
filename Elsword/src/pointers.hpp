#pragma once
#include "common.hpp"
#include "class/vector.hpp"

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};
		uint64_t m_base_address;

		iVector2* m_resolution;
		const char* m_character_name;
		void* m_return_address;
	public:
		void* m_swapchain_methods[19];
		void* m_device_methods[120];
		void* m_context_methods[145];
		D3DPRESENT_PARAMETERS m_d3d_present_param;
	private:
		bool get_swapchain();
		bool swapchain_found = false;
		HWND m_window;
		LPDIRECT3DDEVICE9 m_d3d9_device;
		LPDIRECT3D9 m_direct_d3d9;
	};

	inline pointers* g_pointers{};
}
