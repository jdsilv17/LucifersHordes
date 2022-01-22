// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LucifersHordes : ModuleRules
{
	public LucifersHordes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks", "PrefabricatorRuntime" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "AIModule", "NavigationSystem" });
	}
}
