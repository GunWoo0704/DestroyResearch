#include "ChaosLifecycleLib.h"

// [기본 헤더]
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Engine/World.h"
#include "Physics/Experimental/PhysScene_Chaos.h" 

// [솔버 & 파티클]
#include "PBDRigidsSolver.h"
#include "Chaos/ParticleHandle.h"

// [프록시]
#include "PhysicsProxy/GeometryCollectionPhysicsProxy.h" // UE 5.4 경로

void UChaosLifecycleLib::ApplyAdaptiveLifecycle(
	UGeometryCollectionComponent* GC_Component,
	float SleepThreshold,
	float DampingThreshold,
	float DampingStrength)
{
	if (!GC_Component) return;

	// 1. 프록시 가져오기
	FGeometryCollectionPhysicsProxy* Proxy = static_cast<FGeometryCollectionPhysicsProxy*>(GC_Component->GetPhysicsProxy());
	if (!Proxy) return;

	// 2. [수정 1] 솔버 가져오기 (템플릿 타입 명시 필수!)
	// UE 5.4에서는 어떤 솔버인지 <> 안에 알려줘야 합니다.
	auto* Solver = Proxy->GetSolver<Chaos::FPBDRigidsSolver>();
	if (!Solver) return;

	// 3. [수정 2] 내 파편들만 가져오기 (auto& 사용)
	// ClusteredParticle이라는 복잡한 타입이라서, auto로 받는 게 가장 안전합니다.
	const auto& MyParticles = Proxy->GetSolverParticleHandles();

	// 4. 파편 순회
	for (auto* Handle : MyParticles)
	{
		if (!Handle) continue;

		// Clustered 파티클도 Rigid 파티클의 기능을 다 가지고 있습니다.
		// 따라서 바로 함수를 써도 되고, 확실히 하려면 Cast를 해도 됩니다.
		// 여기서는 auto Handle 자체가 이미 구체적인 타입이므로 바로 씁니다.

		if (Handle->Disabled()) continue;
		if (Handle->Sleeping() || Handle->ObjectState() != Chaos::EObjectStateType::Dynamic)
		{
			continue;
		}

		// [UE 5.4] 속도 측정
		float LinearSpeed = Handle->GetV().Size();

		// [로직 적용]
		if (LinearSpeed < SleepThreshold)
		{
			Handle->SetSleeping(true);
		}
		else if (LinearSpeed < DampingThreshold)
		{
			Handle->SetLinearEtherDrag(DampingStrength);
			Handle->SetAngularEtherDrag(DampingStrength);
		}
		else
		{
			Handle->SetLinearEtherDrag(0.05f);
			Handle->SetAngularEtherDrag(0.05f);
		}
	}
}










