#pragma once

extern int numAI;

void DoGameSetup();
void SetupMiscObjects();

void DoRandomBases();
void SetupBase1(int pNo);
void SetupBase2(int pNo);
void SetupBase3(int pNo);
void SetupBase4(int pNo);
void SetupInitRes(int pNo);

void SetupVictory();
void SetupFailure();

void SetupAI();
void SetupGroups();
void GoHostile();
void EdenReact();