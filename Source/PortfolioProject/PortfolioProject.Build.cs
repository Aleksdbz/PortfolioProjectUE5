// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PortfolioProject : ModuleRules
{
	public PortfolioProject(ReadOnlyTargetRules Target) : base(Target)
	{

		CppStandard = CppStandardVersion.Cpp20;
		PrivateDependencyModuleNames.AddRange(new string[] { "UE5Coro" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem"
		});
	}
}
