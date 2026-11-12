# Portable Map: behavior and implementation

Describes the retained payload **0.2.0**. The behavior prose describes the retained payload; current candidate source and metadata are identified below. Gameplay qualification is a separate requirement.


<!-- source-only-sync -->
## Current source candidate

Source version **0.2.0** is saved from workshop revision `ca32bbf79ce0840d5166a232bdb3a9fdcd761254`. The retained installable payload remains **0.2.0** with its original bytes. This source update does not rebuild or requalify that payload. The current source and metadata define the candidate; gameplay, rendered behavior and co-op remain unqualified for rebuilt bytes.

The authored behavior and lifecycle descriptions below are retained from the published payload. They are not new qualification evidence for the source candidate. The integration table below follows the current candidate metadata.
<!-- /source-only-sync -->

## Behavior

Buy the $200 Portable Map through Modded Shop, assign its native Equipment slot and select it. F12 opens or closes the vanilla map while the device is selected. The provider reuses the real map rather than rendering a separate world view, preserving native map services and any shared top-row controls.

## State and lifecycle

Ownership uses a checked per-world/player sidecar; native loadout stores the tool ID. Current held presentation and map-toggle edges are session state. Unequip/input loss stops device actions, and world/player replacement releases rooted presentation. Purchase, refund and authority checks come through the provider/framework integration.

## Integration and configuration

Runtime dependencies: [shop-framework](https://github.com/swooping-mods/shop-framework), [equipment-framework](https://github.com/swooping-mods/equipment-framework), [hints-framework](https://github.com/swooping-mods/hints-framework).

The [module metadata](../source/mods/portable-map/mod.json) owns the version and declared integration contract. Native modules start at `MoonLab_ModStart`. Game/Unity integrations target the pinned Steam Windows x64 IL2CPP build.

| Service | ABI | Table size |
|---|---:|---|
| Requires `shop-framework.shop` | 1 | at least 56 bytes |
| Requires `equipment-framework.equipment` | 1 | at least 32 bytes |
| Requires `hints-framework.hints` | 1 | at least 24 bytes |

## Implementation sources

- [mod.c](../source/mods/portable-map/mod.c)
- [framework.h](../source/mods/portable-map/framework.h)
- [runtime.h](../source/mods/portable-map/runtime.h)
- [store.h](../source/mods/portable-map/store.h)

## Verification boundary

No additional landmark discovery, remote-player view or custom map save format. Opening the map does not qualify every marker/control consumer, ownership reload or co-op layout.

`python3 build.py --check` verifies the exported source hashes. It does not execute the mod or qualify the behaviors above. Installation and independent build prerequisites are in the [README](../README.md).
