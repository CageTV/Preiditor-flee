#pragma once

namespace PFF
{
    struct Settings
    {
        static Settings* GetSingleton();

        // General
        bool  bEnabled = true;
        float fDetectionRadius = 1024.0f; // trigger range: how close a lit torch/lantern must be
        float fStalkDistance = 2048.0f;   // how far the creature is allowed to drift while stalking
        float fCooldown = 5.0f;           // seconds before the same actor can be re-triggered after an attack
        float fFireCastLinger = 3.0f;     // seconds a burst fire-spell cast (Firebolt/Fireball, not
                                           // held Flames) still counts as "deterred" after the cast
                                           // ends -- an instant cast is shorter than our 500ms poll,
                                           // so without this the flee would collapse the very next tick

        bool bUseKeywordFilter = false; // if true, ONLY actors with the PFF_PredatorFireFlee keyword are affected

        // Predator (naturally hostile -- resumes its own vanilla aggression once the light is gone)
        bool bAffectWolves = true;
        bool bAffectBears = true;
        bool bAffectSabreCats = true;
        bool bAffectTrolls = true;
        bool bAffectIceWraiths = true;
        bool bAffectSpriggans = true; // gated on vanilla SprigganFaction, not PredatorFaction/RKF

        // Prey (naturally passive -- attack is approximated by forcing Aggression; many prey
        // races have no vanilla combat animations/packages at all, so this may not visibly attack)
        bool bAffectDeer = true;
        bool bAffectGoats = true;
        bool bAffectHorkers = true;
        bool bAffectMammoths = true;
        bool bAffectSkeevers = true;

        // Spiders (naturally hostile, same resume-aggression path as predators)
        bool bAffectSpiders = true;

        void Load();
        void Save();
    };
}
