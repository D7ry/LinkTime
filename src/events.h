#pragma once
#include "data.h"
using EventResult = RE::BSEventNotifyControl;

class actionEventHandler : public RE::BSTEventSink<SKSE::ActionEvent>
{
public:
	virtual EventResult ProcessEvent(const SKSE::ActionEvent* a_event, RE::BSTEventSource<SKSE::ActionEvent>* a_eventSource);
	static bool RegisterSink() {
		static actionEventHandler g_eventhandler;
		if (SKSE::GetActionEventSource()) {
			SKSE::GetActionEventSource()->AddEventSink(&g_eventhandler);
			DEBUG("Registered action Event Handler");
			return true;
		} else {
			DEBUG("failed to register action event handler");
			return false;
		}
	}
};

class onHitEventHandler : public RE::BSTEventSink<RE::TESHitEvent>
{
public:

	virtual EventResult ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>* a_eventSource);


	static bool RegisterSink()
	{
		static onHitEventHandler singleton;
		auto ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();

		if (!ScriptEventSource) {
			ERROR("Script event source not found");
			return false;
		}

		ScriptEventSource->AddEventSink(&singleton);

		INFO("Register {}.", typeid(singleton).name());

		return true;
	}

private:
	onHitEventHandler() = default;
	~onHitEventHandler() = default;
	onHitEventHandler(const onHitEventHandler&) = delete;
	onHitEventHandler(onHitEventHandler&&) = delete;
	onHitEventHandler& operator=(const onHitEventHandler&) = delete;
	onHitEventHandler& operator=(onHitEventHandler&&) = delete;

};


class events
{
public:
	static void registerEventSinks() {
		actionEventHandler::RegisterSink();
		//onHitEventHandler::RegisterSink();
	}
};


