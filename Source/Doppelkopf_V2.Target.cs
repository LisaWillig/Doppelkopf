// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Doppelkopf_V2Target : TargetRules
{
	public Doppelkopf_V2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Doppelkopf_V2");
	}
}
