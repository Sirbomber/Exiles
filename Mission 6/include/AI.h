#pragma once

#define numof(array) (sizeof(array)/sizeof(array[0]))
#define autosize(array) numof(array), array

// Setup functions
void SetupAI();
void SetupAiBase();
void SetupAiBase1();
void SetupAiBase2();
void SetupAiBase3();
void SetupAiBase4();

void TransferColony(int pNo, MAP_RECT zone);
