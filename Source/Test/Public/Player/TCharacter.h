// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TCharacter.generated.h"

class UTHealthComponent;
class UTInventoryComponent;
class UCameraComponent;
class USpringArmComponent;
class UTWeaponComponent;
class ATInteractableActor;
class ATBaseWeapon;

UCLASS()
class TEST_API ATCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATCharacter(const FObjectInitializer& ObjectInit);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool AddNewWeapon(ATBaseWeapon* NewWeapon);
	int32 RequestInventoryAmmo(TSubclassOf<ATInteractableActor>& Weapon, int32 Amount);

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	int32 GetInventoryAmmo() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWeaponClipAmmo() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	float DeathTime = 2.0f;

private:
	UFUNCTION()
	void OnDeath();
};
