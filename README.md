# Preditor Flee Fire

An SKSE plugin for Skyrim Special Edition/Anniversary Edition. Wild predators, prey animals, and
spriggans will flee from a lit torch/lantern held in hand, or from an actively-cast Fire, Lightning,
or Poison spell — then stalk at a distance until the deterrent goes away, at which point they
resume their own natural behavior (predators/spiders return to their normal hostility, prey become
aggressive as an approximation since most prey species have no vanilla attack animations at all).

## Features

- **Detection**: triggers on a `TESObjectLIGH` (torch/lantern) equipped in either hand, or on
  actively casting a Fire/Lightning/Poison-elemental Destruction spell (e.g. Firebolt, Sparks,
  Poison Rune) — checked via the same resistance-type tagging the engine itself uses
  (`resistVariable == kResistFire/kResistShock/kPoisonResist`), not a hardcoded spell list, so it
  works with modded spells too. Each element is independently toggleable. Inventory items don't
  count — only what's actually held/cast.
- **Species coverage**: predators and frostbite spiders (gated on vanilla `PredatorFaction`),
  spriggans (their own separate `SprigganFaction` — they aren't members of `PredatorFaction`), and
  prey animals (vanilla `ActorTypeAnimal` keyword, checked on both the actor and its race). Horses,
  dragons, and boss-tier/unique NPCs are always excluded.
- **Flee mechanism**: temporarily sets the creature's `Confidence` actor value to Cowardly while a
  deterrent is present, then restores its original value once it's gone. This lets the engine's own
  combat AI make the flee decision continuously on every one of its own AI think-cycles, rather
  than fighting it with an externally-injected one-shot package (which proved unreliable in
  testing — the AI just kept re-asserting its normal attack behavior against an injected flee).
- **In-game configuration menu** (requires [SKSEMenuFramework](https://www.nexusmods.com/skyrimspecialedition/mods/149705),
  default open key F1): trigger/stalk range, attack cooldown, spell-cast linger duration, a toggle
  for each of Fire/Lightning/Poison spell detection, and a per-species toggle for every covered
  creature type.

## Requirements

- Skyrim Special Edition or Anniversary Edition, SKSE64.
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444).
- [SKSE Menu Framework](https://www.nexusmods.com/skyrimspecialedition/mods/149705) — required at
  runtime for the F1 config menu.

## Installation

Install the release archive with your mod manager like any other SKSE plugin (the DLL goes under
`SKSE/Plugins/`). No ESP.

## Configuration

Open the SKSE Menu Framework overlay (default F1) and find the "Preditor Flee Fire" section.
Settings apply live but do **not** currently persist across a game restart — `Settings::Save()`/
`Load()` are stubs, so re-apply any changes each session for now.

## Building from source

Requires:
- CMake 3.21+
- A C++23-capable MSVC toolset (Visual Studio 2022 Build Tools or newer)
- [vcpkg](https://github.com/microsoft/vcpkg), with `VCPKG_ROOT` set in your environment

```
cmake --preset x64-release
cmake --build --preset x64-release
```

The built DLL lands at `out/build/x64-release/PreditorFleeFire.dll`.

**Important**: the vcpkg triplet must be `x64-windows-static-md` (already set in
`CMakePresets.json`) — the plain `x64-windows` triplet links spdlog/fmt as shared DLLs that don't
get deployed alongside the plugin, causing a runtime load failure (`ERROR_MOD_NOT_FOUND`) even
though the build itself succeeds.

## Known limitations

- Settings don't persist across a restart yet (see Configuration above).
- The F1 menu keybind is owned by SKSE Menu Framework itself and can't be rebound from this plugin.
- Prey species with no vanilla combat AI/animations (most of them) will become hostile via a forced
  `Aggression` value once approached, but may not produce a visible attack — this is a content
  limitation of those actors, not a bug in this plugin.

## License

MIT — see [LICENSE.txt](LICENSE.txt).
