// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FTJ_Proto : ModuleRules
{
	public FTJ_Proto(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
