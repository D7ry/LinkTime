#pragma once
#include "data.h"
namespace MaxsuIFrame	//props to Maxsu
{
	class IsGhostHook
	{
	public:
		static void InstallHook()
		{
			SKSE::AllocTrampoline(1 << 4);
			auto& trampoline = SKSE::GetTrampoline();

			REL::Relocation<std::uintptr_t> ProcessHitFunc{ REL::ID(37673) };
			_IsGhost = trampoline.write_call<5>(ProcessHitFunc.address() + 0x45, IsGhost);
		}

	private:
		static bool IsGhost(const RE::Actor* a_actor)
		{
			DEBUG("IsGhost Trigger!");

			bool iframeActive = false, iframeSate = false;

			if (a_actor->GetGraphVariableBool("bIframeActive", iframeActive) && iframeActive && a_actor->GetGraphVariableBool("bInIframe", iframeSate) && iframeSate) {
				DEBUG("Actor is invulnerable!");
				if (a_actor->IsPlayerRef()) {
					DEBUG("actor is pc!"); 
					auto pc = RE::PlayerCharacter::GetSingleton();
					pc->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->InstantCast(LinkTime_Obj::LinkTime_Dodge_Spell, false, pc, 1, false, settings::dodgeLinkTimeWorldSpeed, pc);
				}
			}

			return _IsGhost(a_actor);
		}

		static inline REL::Relocation<decltype(IsGhost)> _IsGhost;
	};
}