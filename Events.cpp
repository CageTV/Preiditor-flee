#include "Events.h"
#include "Settings.h"

namespace TMD_PFF
{
    FleeManager* FleeManager::GetSingleton()
    {
        static FleeManager singleton;
        return &singleton;
    }

    void FleeManager::OnTick()
    {
        auto* settings = Settings::GetSingleton();
        if (!settings->bEnabled) return;

        static float timer = 0.0f;
        timer += *RE::Offset::g_deltaTime;
        if (timer < 0.5f) return; // run twice per second
        timer = 0.0f;

        auto* player = RE::PlayerCharacter::GetSingleton();
        if (!player || !player->GetParentCell()) return;

        auto cell = player->GetParentCell();
        std::vector<RE::TESObjectREFR*> fireSources;

        // 1. Gather fire sources near player
        cell->ForEachReferenceInRange(player->GetPosition(), settings->fDetectionRadius, [&](RE::TESObjectREFR& ref) {
            if (IsFireSource(&ref)) fireSources.push_back(&ref);
            return true;
        });

        if (fireSources.empty()) return;

        // 2. Check predators near those fire sources
        cell->ForEachReferenceInRange(player->GetPosition(), settings->fDetectionRadius * 2.0f, [&](RE::TESObjectREFR& ref) {
            auto* actor = ref.As<RE::Actor>();
            if (!actor || actor->IsDead() || actor->IsPlayerRef()) return true;
            if (!IsPredator(actor)) return true;
            if (IsOnCooldown(actor)) return true;

            // 3. If predator is near any fire source, make it flee
            for (auto* fire : fireSources) {
                if (actor->GetPosition().GetDistance(fire->GetPosition()) <= settings->fDetectionRadius) {
                    actor->SetFlee(true);
                    actor->EvaluatePackage(); // force AI update
                    SetCooldown(actor);
                    RE::DebugNotification(std::format("{} flees from fire!", actor->GetName()).c_str());
                    break;
                }
            }
            return true;
        });
    }

    bool FleeManager::IsFireSource(RE::TESObjectREFR* ref)
    {
        auto* settings = Settings::GetSingleton();
        if (!ref) return false;

        // Torches - check for torch keyword or equipped torch
        if (settings->bDetectTorches && ref->HasKeywordString("Torch")) return true;

        // Fire spells - check for active magic effect with fire keyword
        if (settings->bDetectFireSpells) {
            if (auto* actor = ref->As<RE::Actor>()) {
                if (actor->GetMagicCaster(RE::MagicSystem::CastingSource::kLeftHand) ||
                    actor->GetMagicCaster(RE::MagicSystem::CastingSource::kRightHand)) {
                    // You'd check the active effect for fire keywords here
                    return true; // simplified
                }
            }
        }

        // Campfires - Furniture with fire keyword
        if (settings->bDetectCampfires && ref->HasKeywordString("Fire")) return true;

        return false;
    }

    bool FleeManager::IsPredator(RE::Actor* actor)
    {
        auto* settings = Settings::GetSingleton();
        if (!actor) return false;

        if (settings->bUseKeywordFilter) {
            return actor->HasKeywordString("TMD_PredatorFireFlee");
        }

        auto* race = actor->GetRace();
        if (!race) return false;

        std::string_view edid = race->GetFormEditorID();
        if (settings->bAffectWolves && edid.contains("Wolf")) return true;
        if (settings->bAffectBears && edid.contains("Bear")) return true;
        if (settings->bAffectSabreCats && edid.contains("SabreCat")) return true;
        if (settings->bAffectTrolls && edid.contains("Troll")) return true;

        return false;
    }

    bool FleeManager::IsOnCooldown(RE::Actor* actor)
    {
        auto now = RE::Calendar::GetSingleton()->GetCurrentGameTime() * 24.0f * 3600.0f;
        auto it = cooldowns.find(actor->GetFormID());
        if (it != cooldowns.end()) {
            return now < it->second;
        }
        return false;
    }

    void FleeManager::SetCooldown(RE::Actor* actor)
    {
        auto* settings = Settings::GetSingleton();
        auto now = RE::Calendar::GetSingleton()->GetCurrentGameTime() * 24.0f * 3600.0f;
        cooldowns[actor->GetFormID()] = now + settings->fCooldown;
    }
}
