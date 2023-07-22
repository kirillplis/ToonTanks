#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (InFireRange())
  {
    RotateTurret(Tank->GetActorLocation());
  }
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
  
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
  if (Tank->bAlive && InFireRange())
  {
    Fire();
  }
}

bool ATower::InFireRange()
{
  if (Tank)
  {
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if (Distance <= FireRange)
    {
      return true;
    }
    return false;
  }
  return false;
}

void ATower::HandleDestruction()
{
  Super::HandleDestruction();
  Destroy();
}