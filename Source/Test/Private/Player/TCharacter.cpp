// Maxim Shtuber

#include "Player/TCharacter.h"
#include "Components/THealthComponent.h"
#include "Components/TCharacterMovementComponent.h"
#include "Components/TInventoryComponent.h"
#include "Components/TWeaponComponent.h"
#include "TPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Objects/Weapons/TBaseWeapon.h"
#include "Objects/TInteractableActor.h"


// Sets default values
ATCharacter::ATCharacter(const FObjectInitializer& ObjectInit) : Super(ObjectInit.SetDefaultSubobjectClass<UTCharacterMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	HealthComponent = CreateDefaultSubobject<UTHealthComponent>("HealthComponent");
	InventoryComponent = CreateDefaultSubobject<UTInventoryComponent>("InventoryComponent");
	WeaponComponent = CreateDefaultSubobject<UTWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ATCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ATCharacter::OnDeath);
}

// Called every frame
void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const auto MovementComponent = Cast<UTCharacterMovementComponent>(GetMovementComponent());
	if (!MovementComponent) return;

	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UTCharacterMovementComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", MovementComponent, &UTCharacterMovementComponent::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ATCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ATCharacter::Jump);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &UTWeaponComponent::Fire);
	PlayerInputComponent->BindAction("NextWeapon", EInputEvent::IE_Pressed, WeaponComponent, &UTWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, InventoryComponent, &UTInventoryComponent::Interact);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, WeaponComponent, &UTWeaponComponent::Reload);

}

void ATCharacter::OnDeath()
{
	if (DeathAnimMontage)
	{
		PlayAnimMontage(DeathAnimMontage);
	}
	const auto MovementComponent = Cast<UTCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->DisableMovement();
	}
	//if (Controller)
	//{
	//	Controller->ChangeState(NAME_Spectating);
	//}
	SetLifeSpan(DeathTime);
}

bool ATCharacter::AddNewWeapon(ATBaseWeapon* NewWeapon)
{
	return WeaponComponent->AddNewWeapon(NewWeapon);
}

int32 ATCharacter::RequestInventoryAmmo(TSubclassOf<ATInteractableActor>& Weapon, int32 Amount)
{
	return InventoryComponent->RequestInventoryAmmo(Weapon, Amount);
}

float ATCharacter::GetHealth() const
{
	return HealthComponent->GetHealth();
}

bool ATCharacter::IsDead() const
{
	return HealthComponent->IsDead();
}

int32 ATCharacter::GetCurrentWeaponClipAmmo() const
{
	return WeaponComponent->GetCurrentWeaponClipAmmo();
}

int32 ATCharacter::GetInventoryAmmo() const
{
	auto Weapon = WeaponComponent->GetCurrentWeapon();
	if (!Weapon) return 0;
	auto AmmoData = Weapon->GetAmmoData();
	return InventoryComponent->GetInventoryAmmo(AmmoData.ObjectClass);
}