// Maxim Shtuber

#include "Components/TCharacterMovementComponent.h"
#include "Player/TCharacter.h"

ATCharacter* UTCharacterMovementComponent::GetCharacter() const
{
	return Cast<ATCharacter>(GetOwner());
}

void UTCharacterMovementComponent::MoveForward(float Amount)
{
	const auto Character = GetCharacter();
	if (!Character) return;
	Character->AddMovementInput(Character->GetActorForwardVector(), Amount);
}

void UTCharacterMovementComponent::MoveRight(float Amount)
{
	const auto Character = GetCharacter();
	if (!Character) return;
	Character->AddMovementInput(Character->GetActorRightVector(), Amount);
}