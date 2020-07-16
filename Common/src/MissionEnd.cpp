#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winuser.h>
#include <vfw.h>

#include <Outpost2DLL.h>
#include <HFL.h>

#include "MissionEnd.h"

#include "OP2Types/OP2Units.h"
#include "Patches.h"
#include "OP2App/CConfig.h"
#include "OP2Types/OP2Game.h"
#include "OP2App/ResManager.h"
#include "OP2App/TApp.h"

static const char* g_VictoryAvi = nullptr;
static const char* g_DefeatAvi = nullptr;

void SetVictoryAvi(const char* newAvi)
{
	g_VictoryAvi = newAvi;
}

void SetDefeatAvi(const char* newAvi)
{
	g_DefeatAvi = newAvi;
}

void __cdecl MissionEnd() {
	static auto& gameTermReasons = reinterpret_cast<GameTermReasons&>(Op2Mem<OP2Game*>(0x56EA98)->gameTermReasons);

	if (gConfigFile.GetInt("Game", "ShowMovies", 1) != 0) {
		switch (gameTermReasons) {
		case GameTermReasons::MissionAccomplished:
			gameTermReasons = GameTermReasons::AutoDemo;  // Prevent the game from playing another cutscene after ours in SP
		case GameTermReasons::VictoryIsSweet:
			if (g_VictoryAvi == nullptr)
			{
				PlayAvi("MPF.AVI", true, "MEBL.AVI", 5000);
			}
			else
			{
				PlayAvi(g_VictoryAvi, true, nullptr, 0);
			}
			break;

		case GameTermReasons::MissionFailed:
			gameTermReasons = GameTermReasons::AutoDemo;  // Prevent the game from playing another cutscene after ours in SP
		case GameTermReasons::YouHaveBeenDefeated:
			if (g_DefeatAvi == nullptr)
			{
				PlayAvi("IP.AVI", true, "MPBL.AVI", 7420);
			}
			else
			{
				PlayAvi(g_DefeatAvi, true, nullptr, 0);
			}
			break;

		default:
			break;
		}
	}
}

