// Maxim Shtuber

#include "TGameModeBase.h"
#include "TPlayerController.h"
#include "TCharacter.h"

ATGameModeBase::ATGameModeBase()
{
	DefaultPawnClass = ATCharacter::StaticClass();
	PlayerControllerClass = ATPlayerController::StaticClass();
}