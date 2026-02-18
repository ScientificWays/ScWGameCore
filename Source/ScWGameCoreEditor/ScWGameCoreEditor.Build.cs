// Scientific Ways

using UnrealBuildTool;
using System.IO; // for Path

public class ScWGameCoreEditor : ModuleRules
{
	public ScWGameCoreEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",

			"AssetTools",

			"ScWGameCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"InputCore",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"UnrealEd",
			"PropertyEditor",
			"AssetManagerEditor",
		});
	}
}