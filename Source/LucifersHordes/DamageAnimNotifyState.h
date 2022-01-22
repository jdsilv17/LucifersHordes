//=====================================================
// Author: Justin DaSilva
// Last Updated: 4/18/2021
//=====================================================

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DamageAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class LUCIFERSHORDES_API UDamageAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// List of Actor to ignore when checking for hits
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> ActorIgnoreList;

	// The Type of way to draw the Sphere Trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EDrawDebugTrace::Type> DrawTraceTypeVar = EDrawDebugTrace::ForOneFrame;

	// name of the socket to start the Trace from (Specific to each Skeletal Mesh)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName StartSocketName;
	// name of the socket to end the Trace at (Specific to each Skeletal Mesh)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName EndSocketName;
	
	// Radius of the Sphere Trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SphereRadius = 15.0f;

	// The color of the Trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor TraceColor = FLinearColor::Red;
	// The color of the Trace when a hit occurs
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor TraceHitColor = FLinearColor::Green;

	// The number of seconds a single Trace will be drawn for
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DrawTime = 5.0f;

	UPROPERTY(EditAnywhere)
		FName Tag;
};
