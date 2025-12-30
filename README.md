# DestroyResearch# ☄️ Chaos Destruction Optimization: Adaptive Lifecycle (UE 5.4)

![Unreal Engine](https://img.shields.io/badge/Unreal_Engine-5.4-black?style=for-the-badge&logo=unrealengine)
![Language](https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Win64-lightgrey?style=for-the-badge&logo=windows)

> **서강대학교 메타버스전문대학원 (Sogang University, Graduate School of Metaverse)** > **Advisor:** Prof. Sang-hoon Park  
> **Project Type:** Master's Thesis Research (Optimization of Physics Simulation)

---

## 📖 프로젝트 개요 (Overview)

이 프로젝트는 **Unreal Engine 5.4**의 **Chaos Physics System**을 활용한 대규모 파괴 시뮬레이션 최적화 라이브러리입니다.

건물 붕괴와 같은 대규모 파괴 씬(Massive Destruction Scene)에서 수천 개의 파편(Geometry Collection Particles)이 생성될 때 발생하는 CPU 병목 현상을 해결하기 위해, 파편의 운동 에너지(Kinetic Energy)를 실시간으로 분석하여 **적응형 생명주기(Adaptive Lifecycle)**를 제어하는 알고리즘을 구현했습니다.

특히, **UE 5.4** 업데이트로 인해 변경된 물리 엔진 API 구조(Solver Access, Particle View, Thread Locking)를 분석하여 안정적으로 마이그레이션된 코드를 제공합니다.

---

## 🚀 핵심 기능 (Key Features)

### 1. Adaptive Physics Control (적응형 물리 제어)
파편의 선형 속도(Linear Velocity)를 모니터링하여 물리 연산 비용을 동적으로 조절합니다.
* **Phase 1: Active (활성)** * 속도가 빠른 초기 파편은 정상적인 물리 시뮬레이션을 수행합니다.
* **Phase 2: Damping (감속 & 안정화)** * 속도가 특정 임계값(`DampingThreshold`) 이하로 떨어지면, **Ether Drag(공기 저항)**를 강제로 높여 미세한 떨림(Jittering)을 방지하고 빠른 정지를 유도합니다.
* **Phase 3: Sleep (수면)** * 속도가 매우 느려지면(`SleepThreshold`) 즉시 **Sleep** 상태로 전환하여 물리 연산에서 제외, CPU 자원을 확보합니다.

### 2. UE 5.4 Chaos Migration (최신 엔진 대응)
UE 5.4에서 변경된 Chaos Destruction 시스템의 API 변경 사항을 완벽하게 반영했습니다.
* **Particle Access:** Deprecated된 `GetActiveParticles()` 대신 **`GetNonDisabledView()`** 사용.
* **Thread Safety:** `FPBDRigidsSolver`의 락 시스템 변경에 대응하여 **`FScopeLock`** 및 표준 락킹 메커니즘 적용.
* **Header & Module:** 5.4 버전에 맞는 올바른 모듈 의존성(`GeometryCollectionEngine`, `ChaosSolverEngine`) 및 헤더 경로 재정립.

---

## 🛠️ 설치 및 설정 (Installation)

### 1. `Build.cs` 설정
프로젝트의 `Build.cs` 파일에 다음 모듈들을 추가해야 합니다.

```csharp
PublicDependencyModuleNames.AddRange(new string[] 
{ 
    "Core", 
    "CoreUObject", 
    "Engine", 
    "InputCore", 
    "GeometryCollectionEngine", // Chaos 파괴 시스템 필수
    "Chaos",                    // 물리 엔진 코어
    "ChaosSolverEngine",        // 솔버 접근용
    "PhysicsCore"               // 물리 타입 정의
});