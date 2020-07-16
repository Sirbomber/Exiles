#pragma once

#include <DisasterCreator.h>

extern int numAI;
extern DisasterCreator DC;

void DoGameSetup();

void DoRandomBases();
void SetupBase1(int pNo);
void SetupBase2(int pNo);
void SetupBase3(int pNo);
void SetupBase4(int pNo);
void SetupInitRes(int pNo);

void SetupDisasters();

void SetupVictory();
void SetupFailure();

void SetupAI();
