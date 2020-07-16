#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <Patches.h>

#include <OP2Types.h>
#include <Outpost2App.h>
#include <string>

#include "ChatCommands.h"

// Max length of chat string
const int size = 36 + 1;

void KillPlayer(int pId, int sourcePlayerNum);

// Chat commands used for debugging purposes.
void ProcessChatCommands(char *chatText, int sourcePlayerNum)
{
	if (!chatText || strcmp(chatText, "/") == 0 || chatText[0] != '/')
		return;

	// Tokenize chat string
	int i = 0;
	char buf[size];
	strcpy_s(buf, sizeof(buf), chatText);
	char word[10][size], *ptok = NULL, *pch = strtok_s(buf, " /", &ptok);
	do
	{
		strcpy_s(word[i], sizeof(word[0]), pch);
		++i;
	} while ((pch = strtok_s(NULL, " ", &ptok)) != 0 && i < (sizeof(word) / sizeof(word[0])));

	// Check command list
	if (strcmp(word[0], "debug") == 0)
	{
		LOCATION mapSize = LOCATION(1024, 1024);
		int xOffset;
		mapSize.Clip();

		// Get actual map dimensions
		if (mapSize.x == 0)
		{
			mapSize.x = 512;
			xOffset = -1;
		}
		else
		{
			mapSize.x -= 32;
			xOffset = +31;
		}
		mapSize.y += 1;

		if (strcmp(word[1], "idkfa") == 0)
		{
			Player[sourcePlayerNum].MarkResearchComplete(12667);
			Player[sourcePlayerNum].SetOre(ExtPlayer[0].GetMaxOre());
			Player[sourcePlayerNum].SetRareOre(ExtPlayer[0].GetMaxRareOre());
		}

		else if (strcmp(word[1], "common") == 0)
		{
			int x, y;
			char *c;
			x = strtol(word[2], &c, 0);
			y = strtol(word[3], &c, 0);
			if (x > 1 && x < mapSize.x && y > 1 && y < mapSize.y)
			{
				TethysGame::CreateBeacon(mapMiningBeacon, x + xOffset, y - 1, 0, 0, 0);
			}
		}

		else if (strcmp(word[1], "rare") == 0)
		{
			int x, y;
			char *c;
			x = strtol(word[2], &c, 0);
			y = strtol(word[3], &c, 0);
			if (x > 1 && x < mapSize.x && y > 1 && y < mapSize.y)
			{
				TethysGame::CreateBeacon(mapMiningBeacon, x + xOffset, y - 1, 1, 0, 0);
			}
		}

		else if (strcmp(word[1], "HELPME") == 0)
		{
			Unit Unit1;
			int x, y;
			char *c;
			x = strtol(word[2], &c, 0);
			y = strtol(word[3], &c, 0);
			if (x > 1 && x < mapSize.x && y > 1 && y < mapSize.y)
			{
				for (int x2 = x; x2 < x + 8; x2++)
				{
					for (int y2 = y; y2 < y + 8; y2++)
					{
						TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(x2 + xOffset, y2 - 1), sourcePlayerNum, mapThorsHammer, 0);
						Unit1.DoSetLights(1);
					}
				}
			}
		}

		else if (strcmp(word[1], "kill") == 0)
		{
			char *c;
			int pId = strtol(word[2], &c, 0);
			// Player parameter can be player ID or player name
			if ((int)*c == 0)
			{
				// Player ID passed in.
				if (pId == -1)
				{
					// Look, I'll be blunt: I get paid for killing the whole country.
					for (int i = 0; i < TethysGame::NoPlayers(); i++)
					{
						KillPlayer(i, sourcePlayerNum);
					}
				}
				else if (pId >= 0 && pId < 6)
				{
					// Kill target player
					KillPlayer(pId, sourcePlayerNum);
				}
			}

			else
			{
				// Player name passed in.
				for (int i = 0; i < TethysGame::NoPlayers(); i++)
				{
					if (strcmp(word[2], ExtPlayer[i].GetPlayerName()) == 0)
					{
						KillPlayer(i, sourcePlayerNum);
					}
				}
			}
		}

		else if (strcmp(word[1], "eden") == 0)
		{
			Player[sourcePlayerNum].GoEden();
		}

		else if (strcmp(word[1], "plymouth") == 0)
		{
			Player[sourcePlayerNum].GoPlymouth();
		}
	}
}

void KillPlayer(int pId, int sourcePlayerNum)
{
	if (strcmp(ExtPlayer[pId].GetPlayerName(), "Sirbomber") == 0)
	{
		TethysGame::AddMessage(-1, -1, "LOL N00B", sourcePlayerNum, sndSavnt227);
		return;
	}

	PlayerUnitEnum LOL(pId);
	Unit Unit1;
	while (LOL.GetNext(Unit1))
	{
		LOCATION curLoc = Unit1.Location();
		short curX = curLoc.x;
		short curY = curLoc.y;

		TethysGame::SetTornado(curX, curY, 50, curX, curY, 1);
	}

	PlayerBuildingEnum N00B(pId, mapNone);
	while (N00B.GetNext(Unit1))
	{
		LOCATION curLoc = Unit1.Location();
		short curX = curLoc.x;
		short curY = curLoc.y;

		TethysGame::SetTornado(curX, curY, 50, curX, curY, 1);
	}
}
