// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TInteractableActor.generated.h"

class ATCharacter;

USTRUCT(BlueprintType)
struct FObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Amount = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<ATInteractableActor> ObjectClass;
};


UCLASS()
class TEST_API ATInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATInteractableActor();

	const FObjectData& GetGeneralData() const { return GeneralData; };

	virtual void FinishInteraction(ATCharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FObjectData GeneralData;

};