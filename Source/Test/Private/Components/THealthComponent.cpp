// Maxim Shtuber

#include "Components/THealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTHealthComponent::UTHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	AActor* Owner = GetOwner();
	if (!Owner) return;
	Owner->OnTakeAnyDamage.AddDynamic(this, &UTHealthComponent::OnTakeAnyDamage);
}

float UTHealthComponent::GetHealth()
{
	return Health;
}

void UTHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

bool UTHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}