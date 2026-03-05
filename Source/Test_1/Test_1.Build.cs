// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Test_1 : ModuleRules
{
	public Test_1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"

		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Test_1",
			"Test_1/Variant_Horror",
			"Test_1/Variant_Horror/UI",
			"Test_1/Variant_Shooter",
			"Test_1/Variant_Shooter/AI",
			"Test_1/Variant_Shooter/UI",
			"Test_1/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
