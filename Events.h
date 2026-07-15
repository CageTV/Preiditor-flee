#pragma once
#include <unordered_map>

namespace TMD_PFF
{
    class FleeManager : public RE::BSTEventSink<RE::TESCellAttachDetachEvent>
    {
    public:
        static FleeManager* GetSingleton();

        void OnTick();

    private:
        std::unordered_map<RE::FormID, float> cooldowns;

        bool IsFireSource(RE::TESObjectREFR* ref);
        bool IsPredator(RE::Actor* actor);
        bool IsOnCooldown(RE::Actor* actor);
        void SetCooldown(RE::Actor* actor);
    };
}
