#include "data.h"
void settings::readSettings() {
	DEBUG("reading settings!");
}

void LinkTime_Obj::getObj() {
	DEBUG("getting linktime obj!");
	LinkTime_Dodge_Spell = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(0x00000D63, "LinkTime.esp");
	FireBall_Spell = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(0x0001C789, "Skyrim.esm");
	if (LinkTime_Dodge_Spell) {
		DEBUG("successfully fetched linktiem spell! {}", LinkTime_Dodge_Spell->GetName());
	}
	else {
		DEBUG("error: link time not found!");
	}
	if (FireBall_Spell) {
		DEBUG("successfully fetched fireball spell!");
	}
}