// Copyright Epic Games, Inc. All Rights Reserved.
//=====================================================
// Modified By: Justin DaSilva, Kurtis McCammon
// Last Updated: 6/20/2021
//=====================================================

#pragma once

#pragma region OG_INCLUDE_DONT_TOUCH
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#pragma endregion

#include "BaseCharacter.h"
#include "UIManagerGameInstance.h"
#include "ItemInterface.h"

#include "LucifersHordesCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDamaged);

UCLASS(config=Game)
class ALucifersHordesCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public: /********************************* PROPERTIES ***********************************/
	ALucifersHordesCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsDodging;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* DodgeAnim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* StepBackAnim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
		UAnimMontage* SmallDamagedAnim;

	UPROPERTY(BlueprintAssignable)
		FOnPlayerDamaged PlayerDamaged; // Event Dispatcher

	uint8 MeleeAttackCount;

public: /********************************* FUNCTIONS ***********************************/

/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
		void ChangeWeapon(AMeleeWeapon* newWeapon);

	UFUNCTION(BlueprintCallable)
		UAbility* TryGetAbility() const;

	void SetAbility(TSubclassOf<UAbility> newAbility);

	//Steven's interaction / interface overrides
	void Interacted();
	bool getInteraction();
	bool setItem(bool aBool);

protected: /********************************* FUNCTIONS ***********************************/
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the game ends or when destroyed
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);
	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);
	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void PrimaryAttack();
	void SecondaryAttack();
	UFUNCTION(BlueprintCallable)
		void ComboAttack();
	UFUNCTION(BlueprintCallable)
		void ResetCombo();

	void Dodge();

	void ActivateMyAbility();

	UFUNCTION(BlueprintCallable)
		void Interact();
	bool isInteracting = false;
	bool isItem = false;

private:
	TArray<UAnimMontage*> LightAttackAnims;
	TArray<UAnimMontage*> HeavyAttackAnims;

	// Scalar for holding the duration of the character animation montages
	float AnimDuration;

	UPROPERTY(EditAnywhere, Category = "Attacking")
		float StrikeControlScalar;

	bool bPrimaryAttack;
	bool bSecondaryAttack;
	bool bSaveAttack;

	class UAIPerceptionStimuliSourceComponent* StimuliForAI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAbility> Ability;

	void Attack();

	/// <summary>
	/// Turns Actor to direction of input when attacking
	/// </summary>
	/// <param name="Direction:">The direction of input</param>
	void StrikeControl(FVector Direction);


	void SetupStimuliSourceComp();

	// combat interface
	//bool AttackBegin_Implementation() override;
	//bool IsAttacking_Implementation(FVector HitLocation) override;
	//bool AttackEnd_Implementation() override;
	//float GetCapsuleColliderRadius_Implementation() const override;
	int32 WhenDamaged_Implementation(AActor* DamageCauser);
	// Death Interface
	int SetDie_Implementation() override;
	int Die_Implementation() override;

	AGroundItem* currentItem;
};

