
#include "SPowerupActor.h"

ASPowerupActor::ASPowerupActor()
{
	PowerupInterval = 0.0f;
	TotalNbOfTicks = 0;
}

void ASPowerupActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASPowerupActor::OnTickPowerup()
{
	++TicksProcessed;
	
	OnPowerupTicked();

	if (TicksProcessed >= TotalNbOfTicks)
	{
		OnExpired();

		// Delete timer
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void ASPowerupActor::ActivatePowerUp()
{
	OnActivated();

	if (PowerupInterval > 0.0f)
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerupActor::OnTickPowerup, PowerupInterval, true);
	else
		OnTickPowerup();
}
