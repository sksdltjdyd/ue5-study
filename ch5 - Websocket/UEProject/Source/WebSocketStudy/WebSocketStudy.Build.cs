// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WebSocketStudy : ModuleRules
{
	public WebSocketStudy(ReadOnlyTargetRules Target) : base(Target)
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
			"WebSockets", // 웹소켓 통신 핵심 모듈
			"JSON", // JSON 데이터 처리 모듈
			"JsonUtilities" // C++에서 JSON 직렬화/역직렬화 지원 모듈
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"WebSocketStudy",
			"WebSocketStudy/Variant_Platforming",
			"WebSocketStudy/Variant_Platforming/Animation",
			"WebSocketStudy/Variant_Combat",
			"WebSocketStudy/Variant_Combat/AI",
			"WebSocketStudy/Variant_Combat/Animation",
			"WebSocketStudy/Variant_Combat/Gameplay",
			"WebSocketStudy/Variant_Combat/Interfaces",
			"WebSocketStudy/Variant_Combat/UI",
			"WebSocketStudy/Variant_SideScrolling",
			"WebSocketStudy/Variant_SideScrolling/AI",
			"WebSocketStudy/Variant_SideScrolling/Gameplay",
			"WebSocketStudy/Variant_SideScrolling/Interfaces",
			"WebSocketStudy/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
