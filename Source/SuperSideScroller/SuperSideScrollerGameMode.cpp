// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperSideScrollerGameMode.h"
#include "SuperSideScrollerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASuperSideScrollerGameMode::ASuperSideScrollerGameMode()
{
	// set default pawn class to our Blueprinted character
	// TEXT 안에 /Game/ 로 시작하는 에셋 경로만 남겨야 합니다.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MainCharacter/Blueprints/BP_SuperSideScroller_MainCharacter"));
	// 경로는 대소문자를 포함하여 정확해야 합니다.

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// 그렇지 않다면, DefaultPawnClass는 초기값인 "Default Pawn"으로 남아있습니다.
}