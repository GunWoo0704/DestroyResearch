// Source/ChaosDestroyResearch/ChaosDestroyResearch.Build.cs

using UnrealBuildTool;

public class ChaosDestroyResearch : ModuleRules
{
    public ChaosDestroyResearch(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",

			// [물리 필수 모듈]
			"GeometryCollectionEngine",
            "Chaos",
            "ChaosSolverEngine",
            "PhysicsCore",
            "ChaosCore"
		});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}