#pragma once

namespace TMD_PFF
{
    struct Settings
    {
        static Settings* GetSingleton();

        // General
        bool  bEnabled = true;
        float fDetectionRadius = 1024.0f; // ~15m in game units
        float fFleeDuration = 10.0f;      // seconds
        float fCooldown = 5.0f;           // seconds before same actor can flee again

        // Fire source toggles
        bool bDetectTorches = true;
        bool bDetectFireSpells = true;
        bool bDetectCampfires = true;
        bool bDetectFireTraps = true;

        // Predator filters
        bool bAffectWolves = true;
        bool bAffectBears = true;
        bool bAffectSabreCats = true;
        bool bAffectTrolls = true;
        bool bUseKeywordFilter = false; // if true, only actors with TMD_PredatorFireFlee keyword

        void Load();
        void Save();
    };
}