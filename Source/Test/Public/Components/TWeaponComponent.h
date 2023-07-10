// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TWeaponComponent.generated.h"

class ATBaseWeapon;
enum FWeaponClasses;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API UTWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTWeaponComponent();

	bool AddNewWeapon(ATBaseWeapon* NewWeapon);
	void Fire();
	void NextWeapon();
	void Reload();
	ATBaseWeapon* GetCurrentWeapon() const;
	int32 GetCurrentWeaponClipAmmo() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	ATBaseWeapon* CurrentWeapon = nullptr;

	TMap<TEnumAsByte<FWeaponClasses>, ATBaseWeapon*> Weapons;
};
