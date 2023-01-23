#pragma once
#include "common.hpp"

namespace big
{
	class player_menu
	{
	public:
		static void render_menu();
		static void add_value();

	private:
		static inline int slot_1{};
		static inline int slot_2{};
		static inline int slot_3{};
		static inline int slot_4{};
		static inline int slot_5{};
		static inline int slot_6{};
		static inline int slot_7{};
		static inline int slot_8{};
		static inline float m_exp_multiplier{};
		static inline const char* const skill_list[]{ "Pyrokinesis","Sclerokinesis","Clairvoyance","Teleportation","Invisibility","Electrokinesis","Duplication","Hypervelocity","Psychokinesis","Psychokinesis","No Skill" };
	};
}