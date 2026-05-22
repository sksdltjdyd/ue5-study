// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "rest_http_testGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class Arest_http_testGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	Arest_http_testGameMode();
};



