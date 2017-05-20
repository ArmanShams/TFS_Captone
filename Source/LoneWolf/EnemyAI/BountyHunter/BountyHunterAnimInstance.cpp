// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "BountyHunterAnimInstance.h"
#include "Engine.h"

void UBountyHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter = Cast<ABountyHunter>(TryGetPawnOwner());
		if (BountyHunter)
		{
			if (BountyHunter->bIsInRange())
			{
				if (BountyHunter->GetEquippedWeapon()->CanFire())
				{
					if (bool t = BountyHunter->bCanTriggerRecoilAnimation())
					{
						bCanBasicAttack = t; //BountyHunter->GetEquippedWeapon()->Fire();
					}
					else
					{
						bCanBasicAttack = false;
					}
				}
				else if(AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(BountyHunter->GetEquippedWeapon()))
				{
					RecastWeapon->Reload();
				}
			}
			//CurrentEnemyState = BountyHunter->CurrentState;

			bIsAiming = BountyHunter->bIsAiming;
			bCanBasicAttack = BountyHunter->bIsInRange();
			bIsBasicAttack = BountyHunter->bIsAttacking;
			bCanSetTrap = BountyHunter->bPlacingTrap;
			bIsDead = BountyHunter->Health <= 0.0f;
			bIsHardCC = BountyHunter->bIsInHardCC;
			
			if (bIsBasicAttack == true)
			{
				//BountyHunter->CurrentlyEquippedWeapon->Fire();
			}
		}	
	}
}

void UBountyHunterAnimInstance::AnimNotify_Shoot()
{
	//if (GetWorld()->HasBegunPlay())
	//{
	//	bIsBasicAttack = true;
	//	BountyHunter->CurrentlyEquippedWeapon->Fire();
	//	BountyHunter->SetBountyHunterState(BountyHunterState::ATTACKING);
	//}
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	//if (GetWorld()->HasBegunPlay())
	//{
	//	bCanSetTrap = true;
	//	BountyHunter->SetBountyHunterState(BountyHunterState::SETTINGTRAP);
	//}
}

void UBountyHunterAnimInstance::AnimNotify_Aim()
{
	//if (GetWorld()->HasBegunPlay())
	//{
	//	bIsAiming = true;
	//	BountyHunter->SetBountyHunterState(BountyHunterState::AIMING);
	//}
}

void UBountyHunterAnimInstance::AnimNotify_ReturnToIdle()
{
	//if (GetWorld()->HasBegunPlay())
	//{
	//	if (BountyHunter->CurrentState(BountyHunterState::IDLE)){}
	//}
}

void UBountyHunterAnimInstance::AnimNotify_Stunned()
{
	//if (GetWorld()->HasBegunPlay())
	//{
	//	bIsHardCC = true;
	//	BountyHunter->SetBountyHunterState(BountyHunterState::HARDCC);
	//}
}