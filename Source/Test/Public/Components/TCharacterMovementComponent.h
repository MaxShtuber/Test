// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TCharacterMovementComponent.generated.h"

class ATCharacter;

/**
 * 
 */
UCLASS()
class TEST_API UTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
private:
	ATCharacter* GetCharacter() const;
};
