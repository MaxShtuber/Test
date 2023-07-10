// Maxim Shtuber

#include "Components/TWeaponComponent.h"

#include "Objects/Weapons/TBaseWeapon.h"
#include "Player/TCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTWeaponComponent::UTWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UTWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}

bool UTWeaponComponent::AddNewWeapon(ATBaseWeapon* NewWeapon)
{
	const auto WeaponClass = NewWeapon->GetWeaponClass();
	if (Weapons.Find(WeaponClass))
	{
		return false;
	}

	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	const auto Character = Cast<ATCharacter>(GetOwner());

	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
	}
	else
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "EquipPoint");
		CurrentWeapon = NewWeapon;
	}
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "WeaponPoint");
	CurrentWeapon->SetOwner(Character);
	Weapons.Add(WeaponClass, NewWeapon);
	return true;
}

void UTWeaponComponent::NextWeapon()
{
	if (Weapons.Num() < 2 || !CurrentWeapon) return;
	auto Iterator = 0;
	for (auto Weapon : Weapons)
	{
		if (CurrentWeapon == Weapon.Value)
		{
			break;
		}
		++Iterator;
	}
	Iterator = ++Iterator % Weapons.Num();
	const auto Character = Cast<ATCharacter>(GetOwner());
	for (auto Weapon : Weapons)
	{
		if (Iterator == 0)
		{
			CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
			CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "EquipPoint");
			CurrentWeapon = Weapon.Value;
			CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "WeaponPoint");
			Character->PlayAnimMontage(CurrentWeapon->EquipAnimMontage);
			break;
		}
		--Iterator;
	}
}

void UTWeaponComponent::Reload()
{
	if (!CurrentWeapon) return;
	if (!CurrentWeapon->Reload()) return;
}

int32 UTWeaponComponent::GetCurrentWeaponClipAmmo() const
{
	return CurrentWeapon ? CurrentWeapon->GetCurrentAmmoClip() : 0;
}

ATBaseWeapon* UTWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}