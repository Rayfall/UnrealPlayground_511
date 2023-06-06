// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Playground_511 : ModuleRules
{
	public Playground_511(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "NavigationSystem", "AIModule", "UMG", "OnlineSubsystem", "OnlineSubsystemUtils" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
    }
}
