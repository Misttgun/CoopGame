
#include "SPowerupActor.h"
#include "Net/UnrealNetwork.h"

ASPowerupActor::ASPowerupActor()
{
	PowerupInterval = 0.0f;
	TotalNbOfTicks = 0;

	bIsPowerupActive = false;

	SetReplicates(true);
}

void ASPowerupActor::OnTickPowerup()
{
	++TicksProcessed;
	
	OnPowerupTicked();

	if (TicksProcessed >= TotalNbOfTicks)
	{
		OnExpired();

		bIsPowerupActive = true;
		OnRep_PowerupActive();

		// Delete timer
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void ASPowerupActor::OnRep_PowerupActive()
{
	OnPowerupStateChanged(bIsPowerupActive);
}

void ASPowerupActor::ActivatePowerUp(AActor* ActivateFor)
{
	OnActivated(ActivateFor);

	bIsPowerupActive = true;
	OnRep_PowerupActive();

	if (PowerupInterval > 0.0f)
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerupActor::OnTickPowerup, PowerupInterval, true);
	else
		OnTickPowerup();
}

void ASPowerupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerupActor, bIsPowerupActive);
}
