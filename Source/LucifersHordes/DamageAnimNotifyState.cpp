//=====================================================
// Author: Justin DaSilva
// Last Updated: 4/20/2021
//=====================================================


#include "DamageAnimNotifyState.h"
#include "HealthComponent.h"
#include "LucifersHordesCharacter.h"
#include "CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "ProceduralMeshComponent.h"

#include "Engine.h"

void UDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	FVector Start = MeshComp->GetSocketLocation(this->StartSocketName);
	FVector End = MeshComp->GetSocketLocation(this->EndSocketName);

	ICombatInterface* ICombat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (ICombat)
		this->SphereRadius = ICombat->Execute_GetCapsuleColliderRadius(MeshComp->GetOwner());

	FHitResult sliceHit;
	FHitResult outHit;

	this->ActorIgnoreList.Add(MeshComp->GetOwner());
	bool slice = UKismetSystemLibrary::LineTraceSingle(MeshComp->GetWorld(), Start, End,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, this->ActorIgnoreList, this->DrawTraceTypeVar.GetValue(),
		sliceHit, true, this->TraceColor, this->TraceHitColor, this->DrawTime);
	bool hit = UKismetSystemLibrary::SphereTraceSingle(MeshComp->GetWorld(), Start, End, this->SphereRadius,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, this->ActorIgnoreList, this->DrawTraceTypeVar.GetValue(),
		outHit, true, this->TraceColor, this->TraceHitColor, this->DrawTime);

	if (hit)
	{
		check(GEngine != nullptr);

		if (!outHit.GetActor())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("WARNING: No Actor Found")));
			return;
		}

		if (slice)
		{
			if (sliceHit.GetActor()->ActorHasTag(this->Tag))
			{

			}
		}
		if (outHit.GetActor()->ActorHasTag(this->Tag))
		{
			if (ICombat)
			{
				// Could move applying damage to here
				this->ActorIgnoreList.Add(outHit.GetActor());
				ICombat->Execute_IsAttacking(MeshComp->GetOwner(), outHit.Location);
			}
		}

		// Display a debug message for five seconds. 
		// The -1 "Key" value argument prevents the message from being updated or refreshed.
		//if (outHit.GetActor())
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Actor Hit: %s"), *outHit.GetActor()->GetName()));
	}
}

void UDamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ICombatInterface* ICombat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (ICombat)
	{
		ICombat->Execute_AttackBegin(MeshComp->GetOwner());
	}
}

void UDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICombatInterface* ICombat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (ICombat)
	{
		ICombat->Execute_AttackEnd(MeshComp->GetOwner());
	}
	this->ActorIgnoreList.Empty();
}
