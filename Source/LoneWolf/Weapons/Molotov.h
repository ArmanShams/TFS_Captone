// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Projectile.h"
#include "Molotov.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API AMolotov : public AProjectile
{
	GENERATED_BODY()

public:
	AMolotov();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetOwner(AActor* NewOwner) override;

	virtual void SetMolotovVelocity(FVector Velocity);

	virtual UProjectileMovementComponent* GetProjectileMovementComponent() override;

protected:
	TSubclassOf<class AActor> FireBPClass;
	AActor* FireBP;

	//class AActor* Owner;


	// Sphere collision component
	//UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	//class USphereComponent* CollisionComponent;

	//UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	//class UStaticMeshComponent* MeshComponent;

	//// Projectile movement component
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	//class UProjectileMovementComponent* ProjectileMovementComponent;

	//UPROPERTY(EditAnywhere, Category = Collision)
	//float SphereRadius = 5.0f;

	//UPROPERTY(EditAnywhere, Category = Projectile)
	//float InitSpeed = 100.0f;

	//UPROPERTY(EditAnywhere, Category = Projectile)
	//float MaxSpeed = 100.0f;

	//UPROPERTY(EditAnywhere, Category = Projectile)
	//float LifeTime = 3.0f;

	////UPROPERTY(EditAnywhere, Category = Projectile)
	////float BulletImpulse = 100.0f;

	//float Damage;

	//class AWeapon_Ranged* WeaponSpawnedThis;

	// Called when projectile hits something 
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
	
};
