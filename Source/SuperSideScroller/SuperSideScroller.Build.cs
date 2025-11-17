// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SuperSideScroller : ModuleRules
{
	public SuperSideScroller(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput" });
        // 이 줄을 추가하여 Public 종속성에 기본 모듈을 포함했는지 확인하세요.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
    }
}
