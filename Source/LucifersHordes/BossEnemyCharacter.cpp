// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LucifersHordesCharacter.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "blackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BossEnemyController.h"
#include "Engine/EngineTypes.h"


int ABossEnemyCharacter::MeleeAttack_Implementation() 
{
    if (this->AttackMontage)
    {
        TryToPlayAnimMontage(this->AttackMontage);
    }
    
    return 0; 
}


int ABossEnemyCharacter::LongRangeAttack_Implementation()
{

    if (this->LongRangeAttack)
    {
        //ABossEnemyController* const cont = Cast<ABossEnemyController>(cont->GetOwner());  

       TryToPlayAnimMontage(this->LongRangeAttack); 
       this->Jump(); 
       this->StopJumping();
       ///////*get the player*/
       // ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); 
       ////// /*Get the players location*/
       ////// FVector const player_loc = player->GetActorLocation(); 
       ////// /*get the player and the bosses distacne from each other*/
       //FVector BossToPlayer(this->GetDistanceTo(player));
       //BossToPlayer.Normalize(); 
       //// FVector direction(BossToPlayer.X, BossToPlayer.Y, 0.0f); 
       //// direction.Normalize(); 

       //this->GetCharacterMovement()->StopActiveMovement(); 
       //this->GetWorld()->GetTimerManager().SetTimer(timer, 1.0f, true, 0.0f);
       //this->GetCharacterMovement()->Launch(BossToPlayer * 1000); 
       //this->GetCharacterMovement()->Launch(FVector::UpVector * 600); 
       //this->GetCharacterMovement()->HandlePendingLaunch(); 


    }
    return 0;
}

void ABossEnemyCharacter::BeginPlay()
{
    Super::BeginPlay(); 

    if (this->Equiped && this->StarterWeapon)
    {
        this->Equiped->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHand"));
        this->Equiped->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftHand"));
    }

}
