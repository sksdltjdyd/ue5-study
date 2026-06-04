// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealStudy : ModuleRules
{
	public UnrealStudy(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UnrealStudy",
			"UnrealStudy/Variant_Platforming",
			"UnrealStudy/Variant_Platforming/Animation",
			"UnrealStudy/Variant_Combat",
			"UnrealStudy/Variant_Combat/AI",
			"UnrealStudy/Variant_Combat/Animation",
			"UnrealStudy/Variant_Combat/Gameplay",
			"UnrealStudy/Variant_Combat/Interfaces",
			"UnrealStudy/Variant_Combat/UI",
			"UnrealStudy/Variant_SideScrolling",
			"UnrealStudy/Variant_SideScrolling/AI",
			"UnrealStudy/Variant_SideScrolling/Gameplay",
			"UnrealStudy/Variant_SideScrolling/Interfaces",
			"UnrealStudy/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
