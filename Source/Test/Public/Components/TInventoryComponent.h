// Maxim Shtuber

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Objects/TInteractableActor.h"

#include "TInventoryComponent.generated.h"

class ATInteractableActor;
class ATBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API UTInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTInventoryComponent();

	UFUNCTION(BlueprintCallable)
	TMap<TSubclassOf<ATInteractableActor>, int32> GetInventory() const {return Inventory; };

	void Interact();
	int32 RequestInventoryAmmo(TSubclassOf<ATInteractableActor>& Weapon, int32 Amount);
	int32 GetInventoryAmmo(TSubclassOf<ATInteractableActor>& Weapon) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float MaxPickupDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<ATInteractableActor>, int32> MaxInventory;
private:
	bool AddItemInInventory(ATInteractableActor* Object);
	bool AddItemInInventory(const FObjectData& Data);
	bool LineTraceHitObject(FHitResult& HitResult);

	TMap<TSubclassOf<ATInteractableActor>, int32> Inventory;
};
