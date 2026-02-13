// Scientific Ways

using UnrealBuildTool;
using System.IO; // for Path

public class ScWGameCore : ModuleRules
{
	public ScWGameCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{
			
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Engine",
			"CoreUObject",

			"PropertyPath",
			"ApplicationCore",

			"AIModule",

			"GameFeatures",
			"ModularGameplay",

			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities",
			"Networking",

			"AsyncMixin",
			"CommonGame",
			"CommonLoadingScreen",
			"GameplayMessageNodes",
			"GameplayMessageRuntime",
			"GameSettings",
			"GameSubtitles",
			"ModularGameplayActors",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"NetCore",
			"InputCore",
			"SlateCore",

			"RHI",
			"UMG",
			"Slate",

			"AudioMixer",
			"AudioModulation",

			"EngineSettings",
			"DeveloperSettings",

			"CommonInput",
			"EnhancedInput",

			"CommonUI",
			"CommonUser",
		});
		// Generate compile errors if using DrawDebug functions in test/shipping builds.
		PublicDefinitions.Add("SHIPPING_DRAW_DEBUG_ERROR=1");

		// Basic setup for External RPC Framework.
		// Functionality within framework will be stripped in shipping to remove vulnerabilities.
		PrivateDependencyModuleNames.Add("ExternalRpcRegistry");
		PrivateDependencyModuleNames.Add("HTTPServer"); // Dependency for ExternalRpcRegistry

		if (Target.Configuration == UnrealTargetConfiguration.Shipping)
		{
			PublicDefinitions.Add("WITH_RPC_REGISTRY=0");
			PublicDefinitions.Add("WITH_HTTPSERVER_LISTENERS=0");
		}
		else
		{
			PublicDefinitions.Add("WITH_RPC_REGISTRY=1");
			PublicDefinitions.Add("WITH_HTTPSERVER_LISTENERS=1");
		}
		SetupGameplayDebuggerSupport(Target);
		SetupIrisSupport(Target);
	}
}
