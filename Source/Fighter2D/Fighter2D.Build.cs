// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fighter2D : ModuleRules
{
	public Fighter2D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "UMG", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});
	}
}
