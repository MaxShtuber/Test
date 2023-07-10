// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "Objects/TInteractableActor.h"
#include "TBaseWeapon.generated.h"

UENUM()
enum FWeaponClasses
{
	BaseWeapon	UMETA(DisplayName = "BaseWeapon"),
	Rifle		UMETA(DisplayName = "Rifle"),
	Launcher	UMETA(DisplayName = "Launcher"),
};

/**
 * 
 */
UCLASS()
class TEST_API ATBaseWeapon : public ATInteractableActor
{
	GENERATED_BODY()
public:
	ATBaseWeapon();

	const FObjectData& GetAmmoData() const { return AmmoData; };

	virtual void FinishInteraction(ATCharacter* Character) override;

	int32 GetCurrentAmmoClip() const;

	TEnumAsByte<FWeaponClasses> GetWeaponClass() const { return WeaponClass; };

	virtual void Fire();
	bool Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* EquipAnimMontage;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FObjectData AmmoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxClipSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<FWeaponClasses> WeaponClass = FWeaponClasses::BaseWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxShootDistance = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 50.0f;
private:
	int32 CurrentAmmoClip = 0;
};
