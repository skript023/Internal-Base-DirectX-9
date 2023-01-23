#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"

namespace big
{
	pointers::pointers() : m_base_address(memory::module(nullptr).begin().as<uint64_t>())
	{
		memory::pattern_batch main_batch;

		if (!this->get_swapchain())
			LOG(WARNING) << "Failed get swapchain";

		m_resolution = (iVector2*)(m_base_address + 0x1095F08);
		m_character_name = (const char*)(m_base_address + 0x10BD223);
		
		main_batch.add("Return Address", "FF 23", [this](memory::handle ptr)
		{
			m_return_address = ptr.as<void*>();
		});

		main_batch.run(memory::module(nullptr));

		this->m_hwnd = FindWindowW(L"Direct3DWindowClass", L"Els Zero");
		if (!this->m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}

	bool pointers::get_swapchain()
	{
		WNDCLASSEX window_class;
		window_class.cbSize = sizeof(WNDCLASSEX);
		window_class.style = CS_HREDRAW | CS_VREDRAW;
		window_class.lpfnWndProc = DefWindowProc;
		window_class.cbClsExtra = 0;
		window_class.cbWndExtra = 0;
		window_class.hInstance = GetModuleHandle(NULL);
		window_class.hIcon = NULL;
		window_class.hCursor = NULL;
		window_class.hbrBackground = NULL;
		window_class.lpszMenuName = NULL;
		window_class.lpszClassName = L"Kiero";
		window_class.hIconSm = NULL;

		::RegisterClassEx(&window_class);

		this->m_window = ::CreateWindow(window_class.lpszClassName, L"Kiero DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, window_class.hInstance, NULL);

		if (this->m_window == NULL)
		{
			return false;
		}

		HMODULE d3d9_module = ::GetModuleHandle(L"d3d9.dll");
		if (d3d9_module == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
			return false;
		}

		void* Direct3DCreate9 = ::GetProcAddress(d3d9_module, "Direct3DCreate9");
		if (Direct3DCreate9 == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
			return false;
		}

		m_direct_d3d9 = ((LPDIRECT3D9(__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION);
		if (m_direct_d3d9 == NULL)
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
			return false;
		}

		D3DDISPLAYMODE DisplayMode;
		if (FAILED(m_direct_d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode)))
		{
			::DestroyWindow(this->m_window);
			::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
			return false;
		}

		m_d3d_present_param.BackBufferWidth = 0;
		m_d3d_present_param.BackBufferHeight = 0;
		m_d3d_present_param.BackBufferFormat = DisplayMode.Format;
		m_d3d_present_param.BackBufferCount = 0;
		m_d3d_present_param.MultiSampleType = D3DMULTISAMPLE_NONE;
		m_d3d_present_param.MultiSampleQuality = NULL;
		m_d3d_present_param.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3d_present_param.hDeviceWindow = this->m_window;
		m_d3d_present_param.Windowed = 1;
		m_d3d_present_param.EnableAutoDepthStencil = 0;
		m_d3d_present_param.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
		m_d3d_present_param.Flags = NULL;
		m_d3d_present_param.FullScreen_RefreshRateInHz = 0;
		m_d3d_present_param.PresentationInterval = 0;

		if (m_direct_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->m_window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &m_d3d_present_param, &m_d3d9_device) < 0)
		{
			m_direct_d3d9->Release();
			::DestroyWindow(this->m_window);
			::UnregisterClass(window_class.lpszClassName, window_class.hInstance);

			return false;
		}

		memcpy(m_device_methods, *(void***)m_d3d9_device, sizeof(m_device_methods));

		m_direct_d3d9->Release();
		m_direct_d3d9 = nullptr;
		m_d3d9_device->Release();
		m_d3d9_device = nullptr;

		::DestroyWindow(this->m_window);
		::UnregisterClass(window_class.lpszClassName, window_class.hInstance);

		return true;
	}
}