// Maxim Shtuber

#include "Objects/Weapons/TBaseWeapon.h"
#include "TCharacter.h"

#include "DrawDebugHelpers.h"

ATBaseWeapon::ATBaseWeapon()
{
	CurrentAmmoClip = MaxClipSize;
}

void ATBaseWeapon::Fire()
{
	const auto Character = Cast<ATCharacter>(GetOwner());
	if (!Character) return;

	const auto Controller = Character->Controller;
	if (!Controller) return;
	if (CurrentAmmoClip == 0)
	{
		Reload();
		return;
	}

	FVector Start;
	FRotator StartRotator;
	FVector End;
	FHitResult HitResult;

	Controller->GetPlayerViewPoint(Start, StartRotator);
	End = Start + Controller->GetControlRotation().Vector() * MaxShootDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 3.0f);
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
	--CurrentAmmoClip;

	const auto Target = Cast<ATCharacter>(HitResult.Actor);
	if (Target)
	{
		Target->TakeDamage(Damage, {}, Controller, Character);
	}
}

void ATBaseWeapon::FinishInteraction(ATCharacter* Character)
{
	if (!Character) return;
	if (!Character->AddNewWeapon(this))
	{
		DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Destroy();
	}
}

bool ATBaseWeapon::Reload()
{
	if (CurrentAmmoClip >= MaxClipSize) return false;

	auto Character = Cast<ATCharacter>(GetOwner());
	if (!Character) return false;

	auto Amount = MaxClipSize - CurrentAmmoClip;
	auto RequestedAmmo = Character->RequestInventoryAmmo(AmmoData.ObjectClass, Amount);

	if (RequestedAmmo == 0) return false;

	CurrentAmmoClip += RequestedAmmo;
	Character->PlayAnimMontage(ReloadAnimMontage);
	return true;
}

int32 ATBaseWeapon::GetCurrentAmmoClip() const
{
	return CurrentAmmoClip;
}