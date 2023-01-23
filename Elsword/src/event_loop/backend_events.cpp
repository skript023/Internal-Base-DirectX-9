#include "backend_events.hpp"
#include "script.hpp"


namespace big
{
	void backend_events::features()
	{
		
	}

	void backend_events::player_skill_event()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}

	void backend_events::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				g_settings->attempt_save();
				features();
			} 
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}