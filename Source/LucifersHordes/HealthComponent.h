//=====================================================
// Author: Justin DaSilva, Christian Chincilla, Kurtis McCammon
// Last Updated: 4/15/2021
//=====================================================

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCIFERSHORDES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
		float GetCurrentHealth() const { return this->CurrentHealth; }
	UFUNCTION(BlueprintCallable)
		void SetCurrentHealth(const float health) { CurrentHealth = health; }

	float GetMaxHealth() const { return this->MaxHealth; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		float CurrentHealth;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	//	float InvicibleTime;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	//	bool bIsInvicible;


	UFUNCTION()
		void TakeDamage
		(
			AActor* DamagedActor, 
			float Damage, 
			const class UDamageType* DamageType, 
			class AController* InstigatedBy,
			AActor* DamageCauser
		); 

		
};
