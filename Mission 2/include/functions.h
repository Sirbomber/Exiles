#ifndef EXILES_01
#define EXILES_01

void DoGameSetup();
void SetupVictory();

void DoRandomBases();
void SetupBase1(int pNo);
void SetupBase2(int pNo);
void SetupBase3(int pNo);
void SetupBase4(int pNo);

void SetupBaseAI(int pAI);
void SetupGroups(int pAI);

void SetupMiscObjects();

void GoHostile();

	// Needed for Arklon's hax
	#define numof(array) (sizeof(array)/sizeof(array[0]))

#endif