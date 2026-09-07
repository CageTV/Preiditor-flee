#include "Menu.h"
#include "Settings.h"
#include <SKSEMenuFramework.h>

namespace PFF::Menu
{
    void Render()
    {
        auto* settings = Settings::GetSingleton();

        ImGui::Checkbox("Enable Mod", &settings->bEnabled);

        ImGui::Separator();
        ImGui::Text("Detection (held torch/lantern, or actively casting a Fire spell -- not inventory)");
        ImGui::SliderFloat("Trigger Range", &settings->fDetectionRadius, 128.0f, 2048.0f, "%.0f");
        ImGui::SliderFloat("Stalk Range", &settings->fStalkDistance, 512.0f, 4096.0f, "%.0f");
        ImGui::SliderFloat("Attack Cooldown", &settings->fCooldown, 1.0f, 30.0f, "%.1f sec");
        ImGui::SliderFloat("Fire Cast Linger", &settings->fFireCastLinger, 0.5f, 10.0f, "%.1f sec");
        ImGui::SameLine();
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("A burst fire spell (Firebolt/Fireball) still counts as a deterrent for this\nlong after the cast ends -- a single cast is shorter than the detection poll.");

        ImGui::Separator();
        ImGui::Text("Predators (already hostile -- resumes attacking on its own once light is gone)");
        ImGui::Checkbox("Wolves", &settings->bAffectWolves);
        ImGui::Checkbox("Bears", &settings->bAffectBears);
        ImGui::Checkbox("Sabre Cats", &settings->bAffectSabreCats);
        ImGui::Checkbox("Trolls", &settings->bAffectTrolls);
        ImGui::Checkbox("Ice Wraiths", &settings->bAffectIceWraiths);
        ImGui::Checkbox("Spriggans", &settings->bAffectSpriggans);

        ImGui::Separator();
        ImGui::Text("Prey (passive by default -- attack is forced via Aggression, may not");
        ImGui::Text("produce real combat animations for species with no vanilla attack AI)");
        ImGui::Checkbox("Deer", &settings->bAffectDeer);
        ImGui::Checkbox("Goats", &settings->bAffectGoats);
        ImGui::Checkbox("Horkers", &settings->bAffectHorkers);
        ImGui::Checkbox("Mammoths", &settings->bAffectMammoths);
        ImGui::Checkbox("Skeevers", &settings->bAffectSkeevers);

        ImGui::Separator();
        ImGui::Text("Spiders");
        ImGui::Checkbox("Frostbite Spiders", &settings->bAffectSpiders);

        ImGui::Separator();
        ImGui::Checkbox("Keyword Only", &settings->bUseKeywordFilter);
        ImGui::SameLine();
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Ignore all species toggles above; only affect actors with keyword PFF_PredatorFireFlee");

        ImGui::Separator();
        if (ImGui::Button("Save Settings")) {
            settings->Save();
            RE::DebugNotification("PFF: Settings saved");
        }
    }

    void Register()
    {
        SKSEMenuFramework::SetSection("Preditor Flee Fire");
        SKSEMenuFramework::AddSectionItem("Settings", Render);
    }
}
