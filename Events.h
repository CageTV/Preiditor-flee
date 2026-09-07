#pragma once
#include <unordered_map>

namespace PFF
{
    enum class SpeciesCategory
    {
        kNone,
        kPredator,
        kPrey,
        kSpider
    };

    enum class FleeBehaviorState
    {
        kNormal,
        kStalking
    };

    struct ActorTracker
    {
        FleeBehaviorState state = FleeBehaviorState::kNormal;
        RE::FormID         lightHolderID = 0;
        float              cooldownUntil = 0.0f; // game-time hours
        float              cachedConfidence = 2.0f; // Confidence AV to restore once the light is gone
        float              deterrentUntil = 0.0f;   // game-time hours; keeps "still deterred" true
                                                      // briefly past the last confirmed torch/fire tick
    };

    // Driven by a worker-thread-paced task (see main.cpp), not an event sink -- no
    // BSTEventSink base is needed here.
    class FleeManager
    {
    public:
        static FleeManager* GetSingleton();

        void OnTick();

    private:
        std::unordered_map<RE::FormID, ActorTracker> trackers;

        RE::TESObjectREFR* FindNearestLitLightHolder(RE::TESObjectCELL* cell, const RE::NiPoint3& origin, float radius);
        RE::TESObjectLIGH*  GetHeldLight(RE::Actor* actor);
        bool                IsCastingFireSpell(RE::Actor* actor);
        bool                HasFireDeterrent(RE::Actor* actor);
        bool                HasKeywordCascade(RE::Actor* actor, RE::BGSKeyword* keyword);
        SpeciesCategory     GetSpeciesCategory(RE::Actor* actor);
        bool                IsExcluded(RE::Actor* actor);
        bool                IsOnCooldown(RE::Actor* actor);
        void                SetCooldown(RE::Actor* actor);
        void                ResumeAggression(RE::Actor* actor, SpeciesCategory category, float confidenceToRestore);
    };
}
