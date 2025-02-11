// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "MinerAnimInstance.h"
#include "EnemyAI/Enemy.h"
#include "EnemyAI/Miner/MinerAI.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "AIController.h"

void UMinerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	ALoneWolfCharacter* Owner = Cast<ALoneWolfCharacter>(TryGetPawnOwner());

	if (Owner != NULL)
	{
		Owner->OnDamageRecieved.AddDynamic(this, &ThisClass::OnDamageTaken);
	}
}

void UMinerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (GetWorld()->HasBegunPlay())
	{
		Super::NativeUpdateAnimation(DeltaSeconds);

		//AMinerAI* RecastEnemy = Cast<AMinerAI>(TryGetPawnOwner())
			
		EnemyCharacter = Cast<AMinerAI>(TryGetPawnOwner());

		if (EnemyCharacter != NULL)
		{
			CurrentMinerState = EnemyCharacter->GetMinerState();
			bCanAttack = EnemyCharacter->GetBTIsInRange();
			bIsDead = EnemyCharacter->Health <= 0.f;
			bIsInHardCC = EnemyCharacter->bIsInHardCC;
			bIsInSoftCC = EnemyCharacter->bIsInSoftCC;
		}
	}
}

void UMinerAnimInstance::AnimNotify_MeleeAttackStart()
{
	if (GetWorld()->HasBegunPlay())
	{
		//UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
		//call a function on our characters to enable colliders on melee weapons
		if (AWeapon_Melee* EquippedWeapon = Cast<AWeapon_Melee>(EnemyCharacter->GetEquippedWeapon()))
		{
			EquippedWeapon->ToggleCollider();
		}
	}
}

void UMinerAnimInstance::AnimNotify_MeleeAttackEnd()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (AWeapon_Melee* EquippedWeapon = Cast<AWeapon_Melee>(EnemyCharacter->GetEquippedWeapon()))
		{
			EquippedWeapon->ToggleCollider();
			EquippedWeapon->bHasHit = false;
		}
	}
}

void UMinerAnimInstance::AnimNotify_ChargeEnd()
{
	//EnemyCharacter = Cast<AMinerAI>(TryGetPawnOwner());
	if (GetWorld()->HasBegunPlay())
	{
		if (EnemyCharacter)
		{
			//EnemyCharacter->SetStatusEffect(CharacterState::NONE);
		}
	}
}

void UMinerAnimInstance::AnimNotify_ApplyStompDamage()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (EnemyCharacter != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("Stomping"));
			EnemyCharacter->Stomp();
		}
	}

}

void UMinerAnimInstance::AnimNotify_ReturnToIdle()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (EnemyCharacter)
		{
			if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
			{
				UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
				BlackboardComponent->SetValueAsBool(TEXT("MarkedToReturnToIdleState"), true);
			}
		}
	}
}

