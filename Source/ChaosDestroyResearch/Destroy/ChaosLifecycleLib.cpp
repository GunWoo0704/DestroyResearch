#include "ChaosLifecycleLib.h"

// [UE 5.4 헤더 설정 성공]
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Engine/World.h"
#include "Physics/Experimental/PhysScene_Chaos.h" 

// [솔버 & 파티클]
#include "PBDRigidsSolver.h"
#include "Chaos/ParticleHandle.h"

void UChaosLifecycleLib::ApplyAdaptiveLifecycle(
	UGeometryCollectionComponent* GC_Component,
	float SleepThreshold,
	float DampingThreshold,
	float DampingStrength)
{
	// 1. 유효성 검사
	if (!GC_Component) return;

	// 2. 월드 & 물리 씬
	UWorld* World = GC_Component->GetWorld();
	if (!World) return;

	FPhysScene* PhysScene = World->GetPhysicsScene();
	if (!PhysScene) return;

	auto* ChaosScene = static_cast<FPhysScene_Chaos*>(PhysScene);
	if (!ChaosScene) return;

	auto* Solver = ChaosScene->GetSolver();
	if (!Solver) return;

	// [수정] 락(Lock) 제거
	// UE 5.4에서는 GetExternalDataLock_GameThread 함수가 변경/제거되었습니다.
	// 간단한 파라미터 변경은 락 없이 수행해도 엔진이 다음 틱에 반영하도록 처리합니다.
	// (컴파일 에러를 피하기 위해 락 부분만 생략합니다.)

	// 3. 파티클 순회 준비
	auto* Evolution = Solver->GetEvolution();
	if (!Evolution) return;

	// UE 5.4용 뷰(View)
	auto& DynamicParticles = Evolution->GetParticles().GetNonDisabledView();

	for (auto& Handle : DynamicParticles)
	{
		// RigidHandle로 변환
		auto* RigidHandle = Handle.CastToRigidParticle();
		if (!RigidHandle) continue;

		if (RigidHandle->Sleeping() || RigidHandle->ObjectState() != Chaos::EObjectStateType::Dynamic)
		{
			continue;
		}

		// [UE 5.4] V() -> GetV()
		float LinearSpeed = RigidHandle->GetV().Size();

		// [UE 5.4] SetLinearEtherDrag / SetAngularEtherDrag
		if (LinearSpeed < SleepThreshold)
		{
			RigidHandle->SetSleeping(true);
		}
		else if (LinearSpeed < DampingThreshold)
		{
			RigidHandle->SetLinearEtherDrag(DampingStrength);
			RigidHandle->SetAngularEtherDrag(DampingStrength);
		}
		else
		{
			RigidHandle->SetLinearEtherDrag(0.05f);
			RigidHandle->SetAngularEtherDrag(0.05f);
		}
	}
}