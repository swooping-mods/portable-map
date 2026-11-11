# Portable Map

Buy the $200 map in Modded Shop; equip it in the native hotbar.

## Install

Install [Moon Sweepers Mod Loader](https://github.com/swooping-mods/moon-sweepers-mod-loader) first.

Download [portable-map-0.2.0.msmod](content/portable-map-0.2.0.msmod), import it with **Install mod package**, then select the mod and its required frameworks.

Required mods: [shop-framework](https://github.com/swooping-mods/shop-framework), [equipment-framework](https://github.com/swooping-mods/equipment-framework), [hints-framework](https://github.com/swooping-mods/hints-framework).

## Controls

- Buy the $200 Portable Map in Modded Shop (Ctrl+Shift+F2); assign it in Inventory and select its hotbar slot.
- F12 opens/closes the vanilla map while the map device is selected.
- Native purchase/equipment/hints integration implemented; gameplay checks deferred.

## Compatibility

Version 0.2.0. Targets the pinned Steam Windows x64 IL2CPP build of Moon Sweepers (Steam app 5335510). On Linux, the game runs through Proton. Experimental: back up saves before using save-affecting mods.

## Build

Run `python3 build.py --check` to verify source hashes, then `python3 build.py` to write a build under `.local/build/`. Requires installed Clang, lld-link and llvm-dlltool.

## Credits

See [CREDITS.txt](CREDITS.txt) and [third-party notices](vendored/THIRD_PARTY_NOTICES.md).
