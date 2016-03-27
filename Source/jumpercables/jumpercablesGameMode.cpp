// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "jumpercables.h"
#include "jumpercablesGameMode.h"
#include "jumpercablesPawn.h"
#include "jumpercablesHud.h"

AjumpercablesGameMode::AjumpercablesGameMode()
{
	DefaultPawnClass = AjumpercablesPawn::StaticClass();
	HUDClass = AjumpercablesHud::StaticClass();
}
