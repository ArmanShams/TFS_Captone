// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BountyHunter.generated.h"

UENUM(BlueprintType)
enum class BountyHunterState : uint8
{
	IDLE					UMETA(DisplayName = "Idle"),
	AIMING					UMETA(DisplayName = "Aiming"),
	ATTACKING				UMETA(DisplayName = "Attacking"),
	FLEEING					UMETA(DisplayName = "Fleeing"),
	HARDCC					UMETA(DisplayName = "Stunned"),
	PATROLLING				UMETA(DisplayName = "Patrolling"),
	SETTINGTRAP				UMETA(DisplayName = "PlacingTrap"),
	SEARCHFORTRAPLOCATIONS	UMETA(DisplayName = "SerachingForTrapLocations")
};

UCLASS(Blueprintable)
class LONEWOLF_API ABountyHunter : public AEnemy
{
	GENERATED_BODY()

public:
	ABountyHunter();

	//Inherited public functions from AEnemy
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual AWeapon* GetEquippedWeapon() override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;
	virtual CharacterState::StatusEffect GetStatusEffect() override;
	virtual bool GetbIsInHardCC() override;
	virtual bool GetbIsInSoftCC() override;
	virtual void Destroyed() override;

	// Implemented public functions
	//virtual bool GetBTIsInRange();
	virtual BountyHunterState GetBountyHunterState();

protected: //Inherited protected functions from AEnemy
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual void Die() override;
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

protected: //Implemented Functions
	virtual void Attack();
	virtual void FixWeaponRotation();
	virtual bool bCanTriggerRecoilAnimation();
	virtual void Flee(ACharacterController* PlayerToFleeFrom);
	virtual void SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SetBountyHunterState(BountyHunterState NewState);

protected:
	//The maximum number of traps he is allowed to put in the world, extra traps will delete the obsolete trap.
	UPROPERTY(EditDefaultsOnly)
	uint8 MaximumTrapsAllowed;
	//Cushion distance from player, safe distance to attack.
	UPROPERTY(EditDefaultsOnly)
	float CushionSpace;
	//Distance to patrol.
	float PatrolDistance;
	//Distance to set traps.
	float SearchingLocations;
	//Trap locations to move to.
	ATrapLocations* FirstTrapLocation;
	ATrapLocations* SecondTrapLocation;
	ATrapLocations* ThirdTrapLocation;
	//UPROPERTY(EditInstanceOnly, Category = Enemy) TArray<class ATargetPoint*> TrapLocations; //Blackboard keys does not accept arrays
	
	//Class for decals.
	AActor* AimLineDecalActor;
	TSubclassOf<AActor> AimLineDecalClass;

	//Class for traps.
	TSubclassOf<class ABearTrap> BearTrapClass;
	ABearTrap* BearTrapPlaced;
	TArray<AActor*> TrapArray;

	//Bounty Hunter Enumerator current state to control animations and functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	BountyHunterState CurrentState;

	//Check on BlackBoard Component target, flee from player character when conditions are met
	ACharacterController* PlayerToFleeFrom;
	//Move to position when in Flee State
	FVector PositionToMove;

	//Blackboard Key Booleans
	bool bSafeAttackingDistance();
	bool bCanAttack();
	bool bSearchingTrapLocations();
	bool bIsPatrolling();
	bool bIsFlee();
	bool bIsStunned;
	bool bIsFleeing;

	//Animation Booleans
	bool bIsAiming;
	bool bIsAttacking;
	bool bPlacingTrap;
	bool bPlayRecoilAnimation;

	//Friendships
	friend class ABearTrap;
	friend class UBountyHunterAnimInstance;
	friend class UBTTask_BountyHunterAim;
	friend class UBTTask_BountyHunterFlee;
	friend class UBTTask_BountyHunterAttack;
	friend class UBTTask_BountyHunterPlaceTrap;
	friend class UBTTask_BountyHunterReturnToIdle;
};