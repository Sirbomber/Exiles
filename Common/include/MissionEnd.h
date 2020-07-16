#pragma once

// Function to call at mission end
void MissionEnd();

// Call these prior to mission end to set victory/defeat AVIs.
void SetVictoryAvi(const char* newAvi);
void SetDefeatAvi(const char* newAvi);