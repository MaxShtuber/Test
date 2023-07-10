// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDamageActor.generated.h"

UCLASS()
class TEST_API ATDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDamageActor();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Radius = 50.0f;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Damage = 10.0f;

};
