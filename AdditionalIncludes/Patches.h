#pragma once

// Patch utilities
inline void* g_hBaseModule = reinterpret_cast<void*>(0x400000);
inline void* g_hInst       = nullptr;

template <typename T = void*>
T Op2Mem(uintptr_t address) { return reinterpret_cast<T>(static_cast<char*>(g_hBaseModule) + (address - 0x400000)); }

// Available patches
bool SetMissionEndHook(bool enable, void(__cdecl*  pfnHook)());					// Disables automatic victory in multiplayer games when only one player remains.  Ideal for co-op games or debugging.  Optionally sets victory/defeat movie.
bool PlayAvi(const char* pFileName, bool isAtMissionEnd, const char* pSecondFile, int secondFileDelay); // Allows you to play an AVI (and optionally interrupt it to play a second one after a delay).  Generally used to play victory/defeat cutscenes.

bool SetNukePatch(bool enable);													// Adds Nuclear Missiles to the Spaceport build list, if tech ID 12667 has been researched.
bool SetEvacuationModuleHook(int numColonistsRequired);							// Allows you to change the number of colonists required to launch the Evacuation Module.  -1 disables this patch.
bool SetMessageHook(bool enable, void (__cdecl* pfnHook)(char* pChatText, int playerNum));	// Use this to define callback functions in response to specific chat message.

