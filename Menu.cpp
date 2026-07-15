#include "Menu.h"
#include "Settings.h"
#include <SKSEMenuFramework.h>
#include <imgui.h>

namespace TMD_PFF::Menu
{
    void Render()
    {
        auto* settings = Settings::GetSingleton();

        ImGui::Checkbox("Enable Mod", &settings->bEnabled);
        
        ImGui::Separator();
        ImGui::Text("Detection");
        ImGui::SliderFloat("Radius", &settings->fDetectionRadius, 256.0f, 4096.0f, "%.0f");
        ImGui::SliderFloat("Flee Duration", &settings->fFleeDuration, 3.0f, 30.0f, "%.1f sec");
        ImGui::SliderFloat("Cooldown", &settings->fCooldown, 1.0f, 20.0f, "%.1f sec");

        ImGui::Separator();
        ImGui::Text("Fire Sources");
        ImGui::Checkbox("Torches", &settings->bDetectTorches);
        ImGui::Checkbox("Fire Spells", &settings->bDetectFireSpells);
        ImGui::Checkbox("Campfires", &settings->bDetectCampfires);
        ImGui::Checkbox("Fire Traps", &settings->bDetectFireTraps);

        ImGui::Separator();
        ImGui::Text("Predator Types");
        ImGui::Checkbox("Wolves", &settings->bAffectWolves);
        ImGui::Checkbox("Bears", &settings->bAffectBears);
        ImGui::Checkbox("Sabre Cats", &settings->bAffectSabreCats);
        ImGui::Checkbox("Trolls", &settings->bAffectTrolls);
        ImGui::Checkbox("Keyword Only", &settings->bUseKeywordFilter);
        ImGui::SameLine();
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Only affect actors with keyword TMD_PredatorFireFlee");

        ImGui::Separator();
        if (ImGui::Button("Save Settings")) {
            settings->Save();
            RE::DebugNotification("TMD_PFF: Settings saved");
        }
    }

    void Register()
    {
        SKSEMenuFramework::SetSection("TMD Predator Flee Fire");
        SKSEMenuFramework::AddSectionItem("Settings", Render);
    }
}
