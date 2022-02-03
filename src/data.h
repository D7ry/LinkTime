#pragma once
struct settings
{
	static void readSettings();
	static inline bool dodgeLinkTime = true;
	static inline bool dodgeLinkTimeRegenStamina = true; //successful triggering dodge link time regenerates stamina to full.
	static inline bool aeroArcheryLinkTime = false;
	
	static inline float dodgeLinkTimeWorldSpeed = 0.1; //how slow enemies become during dodge link time
};

struct LinkTime_Obj
{
	static void getObj();
	static inline RE::SpellItem* LinkTime_Dodge_Spell;
	static inline RE::SpellItem* FireBall_Spell;
};