// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class rest_http_test : ModuleRules
{
	public rest_http_test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"HTTP",
			"Json",
			"JsonUtilities",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {"Slate", "SlateCore"});

		PublicIncludePaths.AddRange(new string[] {
			"rest_http_test",
			"rest_http_test/Variant_Platforming",
			"rest_http_test/Variant_Platforming/Animation",
			"rest_http_test/Variant_Combat",
			"rest_http_test/Variant_Combat/AI",
			"rest_http_test/Variant_Combat/Animation",
			"rest_http_test/Variant_Combat/Gameplay",
			"rest_http_test/Variant_Combat/Interfaces",
			"rest_http_test/Variant_Combat/UI",
			"rest_http_test/Variant_SideScrolling",
			"rest_http_test/Variant_SideScrolling/AI",
			"rest_http_test/Variant_SideScrolling/Gameplay",
			"rest_http_test/Variant_SideScrolling/Interfaces",
			"rest_http_test/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
