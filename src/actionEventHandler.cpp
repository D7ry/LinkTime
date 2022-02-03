#include "events.h"
inline static void processBowDraw() {
	DEBUG("bow draw!");
	if (!settings::aeroArcheryLinkTime) {
		return;
	}
	//RE::PlayerCharacter::GetSingleton()->AddSpell(LinkTime_Obj::LinkTime_Spell);
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (pc->IsInMidair()) {
		DEBUG("pc in mid air!");
		pc->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->InstantCast(LinkTime_Obj::LinkTime_Dodge_Spell, false, pc, 1, false, 1, pc);
		DEBUG("casted linktime!");
	}
}
inline static void processWpnSwing() {
	DEBUG("wpn swing!");
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (pc->GetAttackingWeapon()->object) {
		DEBUG("pc has attacking weapon!");
		DEBUG(pc->GetAttackingWeapon()->object->GetName());
	}
	pc->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->InstantCast(LinkTime_Obj::FireBall_Spell, false, nullptr, 1, false, 0.3, pc);
}
EventResult actionEventHandler::ProcessEvent(const SKSE::ActionEvent* a_event, RE::BSTEventSource<SKSE::ActionEvent>* a_eventSource) {
	if (!a_event || !a_eventSource) {
		INFO("invalid action event!");
		return EventResult::kContinue;
	}
	DEBUG("action event!");
	if (!a_event->actor->IsPlayerRef()) {
		return EventResult::kContinue;
	}
	DEBUG("player event!");
	switch (a_event->type.get()) {
	case SKSE::ActionEvent::Type::kBowDraw: processBowDraw();
	case SKSE::ActionEvent::Type::kWeaponSwing: processWpnSwing();
	}
	
	return EventResult::kContinue;
}