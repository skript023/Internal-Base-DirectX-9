#pragma once
#include "common.hpp"
#include "script.hpp"

namespace big
{
	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr() = default;

		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();

		void tick();
	private:
		void tick_internal();
		template <typename F, typename ...Args>
		void execute_as_script(F&& callback, Args &&...args)
		{
			std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);
		}
	private:
		std::recursive_mutex m_mutex;
		std::vector<std::unique_ptr<script>> m_scripts;
	};

	inline script_mgr g_script_mgr;
}
