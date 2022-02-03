#include "events.h"
using EventResult = RE::BSEventNotifyControl;
using HitFlag = RE::TESHitEvent::Flag;



EventResult onHitEventHandler::ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>* a_eventSource) {
	if (!a_event || !a_eventSource) {
		ERROR("Event Source not found");
		return EventResult::kContinue;
	}

	auto cause = a_event->cause;
	auto target = a_event->target;
	auto source = a_event->source;

	if (!target || !target->IsPlayerRef()) {
		return EventResult::kContinue;
	}

	DEBUG("target is player!");
	if (!cause || !source) {
		DEBUG("invalid hit event!");
		return EventResult::kContinue;
	}

	auto hitsource = RE::TESForm::LookupByID<RE::TESObjectWEAP>(a_event->source);

	if (!hitsource || !hitsource->IsMelee()) {
		DEBUG("Hit Source Is Not Melee Weapon!");
		return EventResult::kContinue;
	}

	bool iframeActive = false, iframeSate = false;

	if (target->GetGraphVariableBool("bIframeActive", iframeActive) && iframeActive && target->GetGraphVariableBool("bInIframe", iframeSate) && iframeSate) {
		DEBUG("player in iframe!");
		auto pc = RE::PlayerCharacter::GetSingleton();
		pc->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->InstantCast(LinkTime_Obj::LinkTime_Dodge_Spell, false, pc, 1, false, settings::dodgeLinkTimeWorldSpeed, pc);
		DEBUG("link spell casted!");
	}

	return EventResult::kContinue;
}
