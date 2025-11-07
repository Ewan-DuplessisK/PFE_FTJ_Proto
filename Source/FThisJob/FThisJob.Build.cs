// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FThisJob : ModuleRules
{
	public FThisJob(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GeometryCollectionEngine", 
			"DataflowEngine", "DataflowCore", "GeometryCollectionNodes", "FieldSystemEngine",
			"Niagara", "CommonUI", "CommonInput","Slate", "SlateCore", "UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
		

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
