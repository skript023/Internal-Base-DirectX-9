#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"

namespace big
{
	HRESULT APIENTRY hooks::endscene(IDirect3DDevice9* this_)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				if ((g_renderer->m_init || g_renderer->init(this_)))
					g_renderer->on_present();
			}

			return g_hooking->m_end_scene_hook.get_original<decltype(&endscene)>()(this_);
		} EXCEPT_CLAUSE

			return NULL;
	}

	HRESULT APIENTRY hooks::on_reset(IDirect3DDevice9* this_, D3DPRESENT_PARAMETERS* param)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->pre_reset();

				auto result = g_hooking->m_on_reset_hook.get_original<decltype(&on_reset)>()(this_, param);

				if (SUCCEEDED(result))
				{
					g_renderer->post_reset();
				}

				return result;
			}

			return g_hooking->m_on_reset_hook.get_original<decltype(&on_reset)>()(this_, param);
		} EXCEPT_CLAUSE

			return NULL;
	}
}