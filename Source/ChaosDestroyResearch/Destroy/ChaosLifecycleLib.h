#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "ChaosLifecycleLib.generated.h"

/**
 * [UE 5.4 연구용] Chaos 파편 생명주기 관리 라이브러리
 */
UCLASS()
class CHAOSDESTROYRESEARCH_API UChaosLifecycleLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 파편의 속도를 감시하여 최적화(Sleep/Damping)를 적용하는 함수
	 */
	UFUNCTION(BlueprintCallable, Category = "Thesis|Optimization")
	static void ApplyAdaptiveLifecycle(
		UGeometryCollectionComponent* GC_Component,
		float SleepThreshold = 10.0f,
		float DampingThreshold = 100.0f,
		float DampingStrength = 10.0f
	);
};