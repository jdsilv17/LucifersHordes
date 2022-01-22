// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Unreal
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

//Ours
#include "ItemTypes.h"

//Generate
#include "GroundItem.generated.h"

class ULH_ItemAsset;
class AMeleeWeapon;
class URelic;
class UAbility;
class UParticleSystemComponent;
class UUserWidget;
class UBillboardComponent;
class USoundCue;
class UAudioComponent;

UCLASS(BlueprintType)
class LUCIFERSHORDES_API AGroundItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		bool bReadyToEquip = false;
public:	
	// Sets default values for this actor's properties
	AGroundItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(EditDefaultsOnly)
		UBillboardComponent* ItemBillboard;

	UPROPERTY(EditDefaultsOnly)
		USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere)
		float Variance = 0;

	UPROPERTY(EditAnywhere)
		bool destroyOnPickup = true;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystemComponent* PSC;
	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ItemEffect;

	FVector OriginalLoc;

	FRotator OriginalRot;

	bool bUp = true;

	bool bIsWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (EditCondition = "itemType == EItemType::Weapon"))
		TSubclassOf<AMeleeWeapon> weapon;

	UPROPERTY(EditAnywhere, Meta = (EditCondition = "itemType == EItemType::Relic"))
		TSubclassOf<URelic> relic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (EditCondition = "itemType == EItemType::Ability || itemType == EItemType::Weapon"))
		TSubclassOf<UAbility> ability;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType itemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAbilityModified;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMyRelic(TSubclassOf<URelic> newRelic);

	void SetMyWeapon(TSubclassOf<AMeleeWeapon> newWeapon);

	void SetMyAbility(TSubclassOf<UAbility> newAbilty);

	void SetWepAbility(TSubclassOf<UAbility> newAbilty);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(BlueprintReadOnly)
		FText ItemName;
	UPROPERTY(BlueprintReadOnly)
		FText ItemDescription;
	UPROPERTY(BlueprintReadOnly)
		FText Damage;
	UPROPERTY(BlueprintReadOnly)
		FText DamageTypes;
	UPROPERTY(BlueprintReadOnly)
		FText ModifierValues;
	UPROPERTY(BlueprintReadOnly)
		FText Modifiers;

	UPROPERTY(BluePrintReadOnly)
		FText AbilityName;
	UPROPERTY(BlueprintReadOnly)
		FText AbilityDesc;
	UPROPERTY(BlueprintReadOnly)
		UTexture2D* AbilityIcon;

	UPROPERTY(BlueprintReadOnly)
		UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> ItemUITemplate;
	UPROPERTY()
		UUserWidget* itemUI;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		USoundCue* ItemSFXCue;

	UAudioComponent* ItemSFX;

private:
	AActor* actorRef = nullptr;
	void giveItem();
	void setBillboard();
};
