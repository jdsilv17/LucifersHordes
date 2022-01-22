// Copyright Epic Games, Inc. All Rights Reserved.
//=====================================================
// Modified By: Justin DaSilva, Kurtis McCammon
// Last Updated: 6/23/2021
//=====================================================

//Other Unreal Headers
#include "LucifersHordesCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LH_GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


//////////////////////////////////////////////////////////////////////////
// ALucifersHordesCharacter
ALucifersHordesCharacter::ALucifersHordesCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Set Attcking Properties
	//this->bIsAttacking = false;
	this->bPrimaryAttack = false;
	this->bSecondaryAttack = false;
	this->bSaveAttack = false;
	this->StrikeControlScalar = 2.0f;

	this->bIsDodging = false; 
	this->bCanMove = true;
	this->MeleeAttackCount = 0;
	this->AnimDuration = 0.0f;

	SetupStimuliSourceComp();
}

void ALucifersHordesCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto playerController = Cast<APlayerController>(GetController());
	if (IsValid(playerController) && !playerController->InputEnabled()) EnableInput(playerController);

	// "Loading" in save data
	bool bData_loaded = false;

	//auto gameInst = Cast<UUIManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//if (gameInst)
	//	bData_loaded = gameInst->LoadPlayerData(this);

	if (!bData_loaded && this->Equiped && this->StarterWeapon)
	{
		this->Equiped->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHandWeapon"));

		// Set the attack animation for the equiped weapon
		this->LightAttackAnims = this->Equiped->GetPrimaryAttackAnims();
	}

	// Slot ability so it is ready for use
	if (this->AbililtyComponent && this->TryGetAbility())
	{
		this->AbililtyComponent->AddAbility(this->TryGetAbility());
	}

	this->bCanMove = true;
}

void ALucifersHordesCharacter::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

	// Saving Player Data
	//auto gameInst = Cast<UUIManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//if (gameInst)
	//{
	//	gameInst->SavePlayerData(this);
	//}
}

//////////////////////////////////////////////////////////////////////////
// Input
void ALucifersHordesCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ALucifersHordesCharacter::PrimaryAttack);
	// works for keyboard and gamepad keys
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Repeat, this, &ALucifersHordesCharacter::PrimaryAttack);
	//PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ALucifersHordesCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &ABaseCharacter::ActivateWeaponAbility);
	PlayerInputComponent->BindAction("SecondaryAbility", IE_Pressed, this, &ALucifersHordesCharacter::ActivateMyAbility);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ALucifersHordesCharacter::Dodge);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALucifersHordesCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALucifersHordesCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALucifersHordesCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALucifersHordesCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALucifersHordesCharacter::LookUpAtRate);
}

void ALucifersHordesCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(10, 5.0f, FColor::Red, FString::SanitizeFloat((GetFollowCamera()->GetComponentLocation() - GetActorLocation()).Size()));

	//
	// maybe make function to wrap all this stuf in and call it with timer
	//
	if (this->bDead)
	{
		this->Execute_Die(this);
	}
	if (this->bIsDamaged)
	{
		//if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(this->SmallDamagedAnim))
		//{
		//	this->bIsInvincible = false;
		//	this->bIsDamaged = false;
		//}
		if (this->bIsInvincible)
		{
			this->InvincibleTime -= DeltaTime;
			if (this->InvincibleTime <= 0.0f)
			{
				this->bIsInvincible = false;
				this->InvincibleTime = 2.0f;
			}
		}
		else
			this->bIsDamaged = false;
	}
	if (this->bIsDodging)
	{
		// get anim instance, get montage is playing, set isDodging to false
		if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(this->DodgeAnim)
			&& !GetMesh()->GetAnimInstance()->Montage_IsPlaying(this->StepBackAnim)
			)
		{
			this->bIsInvincible = false;
			this->bIsDodging = false;
		}
	}

	this->AnimDuration -= DeltaTime;
}

void ALucifersHordesCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * this->BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALucifersHordesCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * this->BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALucifersHordesCharacter::PrimaryAttack()
{
	check(this->LightAttackAnims.Num() != 0 || this->HeavyAttackAnims.Num() != 0);

	if (this->bIsDying)
		return;

	if (this->bIsAttacking && !this->bSecondaryAttack) // if they are already attacking
	{
		this->bPrimaryAttack = true;
		this->bSaveAttack = true;
	}
	else if (!this->bIsAttacking)
	{
		this->bIsAttacking = true;
		this->bPrimaryAttack = true;

		this->Attack();
	}
	
}

void ALucifersHordesCharacter::SecondaryAttack()
{
	check(this->LightAttackAnims.Num() != 0 || this->HeavyAttackAnims.Num() != 0);

	if (this->bIsDying)
		return;

	if (this->bIsAttacking) // if they are already attacking
	{
		this->bSecondaryAttack = true;
		this->bSaveAttack = true;
	}
	else if (!this->bIsAttacking)
	{
		this->bIsAttacking = true;
		this->bSecondaryAttack = true;

		this->Attack();
	}
}

void ALucifersHordesCharacter::Attack()
{
	check(GEngine != nullptr);

	this->AnimDuration = 0.0f;

	if (	(this->bPrimaryAttack && this->MeleeAttackCount >= this->LightAttackAnims.Num())
		||	(this->bSecondaryAttack && this->MeleeAttackCount >= this->HeavyAttackAnims.Num())
		)
	{
		this->MeleeAttackCount = 0;
		return;
	}
	// when you move this to weapons change the interface to take these bools
	if (!this->bIsDodging)
	{
		if (this->bPrimaryAttack)
		{
			this->AnimDuration = this->PlayAnimMontage(this->LightAttackAnims[this->MeleeAttackCount++], this->GetEquipedWeapon()->GetAttackSpeed());
			this->bPrimaryAttack = false;
		}
		else if (this->bSecondaryAttack)
		{
			this->AnimDuration = this->PlayAnimMontage(this->HeavyAttackAnims[this->MeleeAttackCount], this->GetEquipedWeapon()->GetAttackSpeed());
			this->bSecondaryAttack = false;
			this->MeleeAttackCount = 0;
		}
	}
	else
		this->ResetCombo();
}

void ALucifersHordesCharacter::ComboAttack()
{
	if (this->bSaveAttack)
	{
		this->bSaveAttack = false;
		this->Attack();
	}
}

void ALucifersHordesCharacter::ResetCombo()
{
	check(GEngine != nullptr);

	this->bIsAttacking = false;
	this->bPrimaryAttack = false;
	this->bSecondaryAttack = false;
	this->bSaveAttack = false;
	this->MeleeAttackCount = 0;
}

void ALucifersHordesCharacter::Dodge()
{
	// reset combo because this interupts attacking
	this->ResetCombo();

	if (this->bIsDying)
		return;

	// if we are falling we dont want to dodge
	if (GetCharacterMovement()->IsFalling())
		return;

	float maxDegreesPerSec = 720.0f;
	float maxRotation = 180.0f;
	
	if (!this->bIsDodging)
	{

		this->bIsDodging = true;
		// if we are moving we want to perform a dodge roll in the direction of input
		if ((GetCharacterMovement()->GetLastInputVector() != FVector::ZeroVector))
		{
			FVector lastDirection = GetCharacterMovement()->GetLastInputVector();
			SetActorRotation(lastDirection.Rotation().Quaternion());
			this->bIsInvincible = true;
			// Play high priority montage
			if (this->DodgeAnim)
				PlayHighPriorityAnimMontage(this->DodgeAnim, 1.25f); // High priority
		}
		// else if they aren't moving, perform a stepback dodge
		else
		{
			this->bIsInvincible = true;
			// Play low priority montage
			if (this->StepBackAnim)
				PlayHighPriorityAnimMontage(this->StepBackAnim, 1.25f);
		}
	}
	/* Tick sets bIsDodging to false*/
}

void ALucifersHordesCharacter::ActivateMyAbility()
{
	if (!this->AbililtyComponent->bActivated && this->TryGetAbility())
	{
		this->AbililtyComponent->ActivateAbility(this->TryGetAbility()->GetDevName());
	}
}

void ALucifersHordesCharacter::StrikeControl(FVector Direction)
{
	check(GEngine != nullptr)
	if (this->bIsAttacking)
	{
		FVector Right = GetActorRightVector();
		float tempDot = FVector::DotProduct(Right, Direction);
		float dot = (tempDot <= 0.000001f && tempDot > -0.000001f) ? -1.0f : tempDot;

		FRotator NewRot(0.0f, dot * this->StrikeControlScalar, 0.0f);
		AddActorWorldRotation(NewRot.Quaternion());
	}
}

void ALucifersHordesCharacter::ChangeWeapon(AMeleeWeapon* newWeapon)
{
	auto temp = this->Equiped;
	this->Equiped = newWeapon;

	if (temp->TryGetAbility())
		this->AbililtyComponent->RemoveAbility(temp->TryGetAbility()->GetName());

	temp->Destroy();

	this->Equiped->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHandWeapon"));

	this->AbililtyComponent->AddAbility(this->GetEquipedWeapon()->TryGetAbility());

	// Set the attack animation for the equiped weapon
	this->LightAttackAnims = this->Equiped->GetPrimaryAttackAnims();
}

UAbility* ALucifersHordesCharacter::TryGetAbility() const
{
	UAbility* abilityToGet = this->Ability.GetDefaultObject();

	if (abilityToGet) return abilityToGet;

	return nullptr;
}

void ALucifersHordesCharacter::SetAbility(TSubclassOf<UAbility> newAbility)
{
	if (TryGetAbility()) {
		this->AbililtyComponent->RemoveAbility(TryGetAbility()->GetDevName());
	}
	if (!newAbility)
		this->Ability = nullptr;
	else {
		this->Ability = newAbility;
		this->AbililtyComponent->AddPAbility(this->TryGetAbility());
	}

}

void ALucifersHordesCharacter::SetupStimuliSourceComp()
{
	StimuliForAI = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuli"));

	StimuliForAI->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimuliForAI->RegisterWithPerceptionSystem();
}

//bool ALucifersHordesCharacter::AttackBegin_Implementation()
//{
//
//	if (this->bIsAttacking && this->Equiped && this->Equiped->GetParticleSystem())
//	{
//		this->GetEquipedWeapon()->SetActorEnableCollision(true);
//		return true;
//	}
//	return false;
//}
//
//bool ALucifersHordesCharacter::IsAttacking_Implementation(FVector HitLocation)
//{
//	if (this->bIsAttacking && this->Equiped && this->Equiped->GetParticleSystem())
//	{
//		this->GetEquipedWeapon()->SetHitLocation(HitLocation);
//		return true;
//	}
//	return false;
//}
//
//bool ALucifersHordesCharacter::AttackEnd_Implementation()
//{
//	if (this->bIsAttacking)
//	{
//		this->GetEquipedWeapon()->SetActorEnableCollision(false);
//		return true;
//	}
//	return false;
//}
//
//float ALucifersHordesCharacter::GetCapsuleColliderRadius_Implementation() const
//{
//	float radius = 0.0;
//	if (this->Equiped)
//	{
//		radius = this->Equiped->GetCapsuleComp()->GetUnscaledCapsuleRadius();
//	}
//	return radius;
//}

int32 ALucifersHordesCharacter::WhenDamaged_Implementation(AActor* DamageCauser)
{
	if (this->bIsDying)
		return 0;

	if (!this->bIsInvincible)
	{
		this->ResetCombo();

		this->PlayerDamaged.Broadcast();

		this->bIsInvincible = true;
		this->bIsDamaged = true;

		if (this->SmallDamagedAnim)
			this->PlayHighPriorityAnimMontage(this->SmallDamagedAnim);
	}

	return this->bIsDamaged;
}

int ALucifersHordesCharacter::SetDie_Implementation()
{
	// Disable input when dying
	auto playerController = Cast<APlayerController>(GetController());
	if (IsValid(playerController)) DisableInput(playerController);

	//Increment death count for stats
	UUIManagerGameInstance* uiManager = Cast<UUIManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	uiManager->playerDeathCount++;

	this->bIsInvincible = true; // temp fix
	this->SetActorEnableCollision(false);
	return this->bIsDying = true;
}

int ALucifersHordesCharacter::Die_Implementation()
{
	// set to true in anim BP
	return this->bDead;
}

void ALucifersHordesCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && this->bCanMove)
	{
		// find out which way is forward
		const FRotator Rotation = GetFollowCamera()->GetComponentRotation(); Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, "ForwardInputDir: " + (Direction * Value).ToString());

		this->StrikeControl(Direction * Value);

		AddMovementInput(Direction, Value);
	}
}

void ALucifersHordesCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && this->bCanMove)
	{
		// find out which way is right
		const FRotator Rotation = GetFollowCamera()->GetComponentRotation();// Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		//GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow, "RightInputDir: " + (Direction * Value).ToString());

		this->StrikeControl(Direction * Value);

		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ALucifersHordesCharacter::Interact()
{
	//Function used for interacting with objects in the world.
	if (isItem)
	{
		isInteracting = true;
	}
	return;
}

void ALucifersHordesCharacter::Interacted()
{
	isInteracting = false;
	isItem = false;
}

bool ALucifersHordesCharacter::getInteraction()
{
	return isInteracting;
}

bool ALucifersHordesCharacter::setItem(bool aBool)
{
	return isItem = aBool;
}