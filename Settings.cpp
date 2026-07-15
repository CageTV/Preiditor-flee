#include "Settings.h"

namespace TMD_PFF
{
    Settings* Settings::GetSingleton()
    {
        static Settings singleton;
        return &singleton;
    }

    void Settings::Load() 
    {
        // We'll add INI loading later
    }
    
    void Settings::Save() 
    {
        // We'll add INI saving later  
    }
}