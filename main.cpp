#include "Menu.h"
#include "Events.h"
#include "Settings.h"

extern "C" DLLEXPORT bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    
    auto* messaging = SKSE::GetMessagingInterface();
    messaging->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
        if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
            TMD_PFF::Settings::GetSingleton()->Load();
            TMD_PFF::Menu::Register();
            
            // Register tick handler
            auto* events = TMD_PFF::FleeManager::GetSingleton();
            SKSE::GetTaskInterface()->AddTask([]() {
                RE::Main::GetSingleton()->updateCallbacks.push_back([](float) {
                    TMD_PFF::FleeManager::GetSingleton()->OnTick();
                });
            });
        }
    });

    return true;
}