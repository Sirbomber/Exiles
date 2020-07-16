#pragma once

// Setup functions
void SetupAI();
void SetupAiBase();
void SetupDefenders_IonDrive();
void SetupDefenders_FusionDrive();
void SetupDefenders_FuelingSystems();
void SetupDefenders_CommandModule();
void SetupGroup_HighPlateau();
void SetupGroup_RandomCanyonLynx();
void SetupGroup_RandomPanthers();
void SetupGroup_Patrol();
void SetupGroup_FusionDriveTrap();
void Setup_RandomGuardPosts();

// AI response functions
void TriggerFusionDriveTrap(UnitEx wTruck);
void TriggerFuelingTrap_Decoy(UnitEx wTruck);
void TriggerCommandTrap(UnitEx wTruck);
void TriggerHabitatTrap(UnitEx wTruck);
void TriggerPanic();