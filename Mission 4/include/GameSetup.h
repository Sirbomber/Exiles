#pragma once

void DoGameSetup();
void SetupMiscObjects();
void SetupDisasters();
void SetLavaAllowed();

// Functions for setting up volcano animations
void SouthEastFlowAni ( int x, int y);
void SouthFlowAni( int x, int y);
void SouthWestFlowAni ( int x, int y);

// Functions for stopping volcano animations
void SouthEastFlowStopAni ( int x, int y);
void SouthFlowStopAni( int x, int y);
void SouthWestFlowStopAni ( int x, int y);