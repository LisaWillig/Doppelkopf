// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Doppelkopf_V2 : ModuleRules
{
	public Doppelkopf_V2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "OnlineSubsystem" });
	}
}
