// Maxim Shtuber

#include "Objects/TInteractableActor.h"

// Sets default values
ATInteractableActor::ATInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATInteractableActor::FinishInteraction(ATCharacter* Character)
{
	Destroy();
}