#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <OP2Types.h>
#include <Outpost2App.h>

#include "AI.h"

extern int numPlym;

PlymouthAiData P;

struct WaveDefs
{

};
void InitPlymouth()
{
	for (int i = 0; i < 7; i++)
	{
		P.pfg[i] = CreateFightGroup(numPlym);
	}

	// Initial attack
	P.pfg[0].SetRect(MAP_RECT(13 + 31, 50 - 1, 26 + 31, 55 - 1));
	UnitEx Unit1;
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(18 + 31, 41 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(21 + 31, 39 - 1), numPlym, mapRPG, 2);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(21 + 31, 44 - 1), numPlym, mapEMP, 2);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(19 + 31, 45 - 1), numPlym, mapEMP, 2);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(20 + 31, 47 - 1), numPlym, mapRPG, 2);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(14 + 31, 14 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15 + 31, 13 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(16 + 31, 12 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(17 + 31, 11 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(18 + 31, 10 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(19 + 31, 9 - 1), numPlym, mapRPG, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(14 + 31, 13 - 1), numPlym, mapEMP, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15 + 31, 12 - 1), numPlym, mapEMP, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(16 + 31, 11 - 1), numPlym, mapEMP, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(17 + 31, 10 - 1), numPlym, mapEMP, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(18 + 31, 9 - 1), numPlym, mapEMP, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(19 + 31, 8 - 1), numPlym, mapEMP, 1);
	Unit1.DoSetLights(1);
	P.pfg[0].TakeUnit(Unit1);

}