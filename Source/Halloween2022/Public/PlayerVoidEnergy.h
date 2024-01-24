#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DBDTunableRowHandle.h"
#include "Components/ActorComponent.h"
#include "EVoidEnergyType.h"
#include "Templates/SubclassOf.h"
#include "EVoidEnergyChangeReason.h"
#include "PlayerVoidEnergy.generated.h"

class ADBDPlayer;
class UStatusEffect;
class UVoidEnergyOrbSpawner;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class HALLOWEEN2022_API UPlayerVoidEnergy : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Replicated)
	EVoidEnergyChangeReason _reasonLastVoidEnergyChangeOccurred;

private:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentVoidEnergy, Transient)
	int32 _currentVoidEnergy;

	UPROPERTY(ReplicatedUsing=OnRep_TotalVoidEnergySpent, Transient)
	int32 _totalVoidEnergySpent;

	UPROPERTY(EditDefaultsOnly)
	TArray<FDBDTunableRowHandle> _voidEnergyLevelsToStartNextTier;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _maxEnergyOnPlayerAllowed;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _amountLostOnDownAsSurvivor;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _amountGainedOnDownAsKiller;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _amountGainedOnStunAsSurvivor;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _amountLostOnStunAsKiller;

	UPROPERTY(EditDefaultsOnly)
	TArray<FDBDTunableRowHandle> _hasteValueTiers;

	UPROPERTY(EditDefaultsOnly)
	FDBDTunableRowHandle _timeHasteEffectLasts;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffect> _hasteStatusEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UVoidEnergyOrbSpawner> _voidEnergyOrbSpawnerClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> _scoreEventTiers;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> _scoreEventTiersWithoutOffering;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnVoidEnergyLost(EVoidEnergyChangeReason changeReason);

	UFUNCTION(BlueprintImplementableEvent)
	void OnVoidEnergyGained();

private:
	UFUNCTION()
	void OnRep_TotalVoidEnergySpent(int32 previousTotalVoidEnergySpent);

	UFUNCTION()
	void OnRep_CurrentVoidEnergy(int32 previousEnergyCount);

	UFUNCTION()
	void OnLocallyObservedChanged(ADBDPlayer* player);

	UFUNCTION()
	void OnLocallyControlledChanged();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ShowVoidEnergyChanges(const int32 previousVoidEnergyCount, const int32 newVoidEnergyCount);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_AddVoidEnergy(const int32 amountToAdd, const EVoidEnergyType voidEnergyType);

public:
	UFUNCTION(BlueprintPure)
	int32 GetTotalVoidEnergyDeposited() const;

	UFUNCTION(BlueprintPure)
	int32 GetMaxAmountOfVoidEnergyCanReceive() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentVoidEnergyCount() const;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPlayerVoidEnergy();
};

FORCEINLINE uint32 GetTypeHash(const UPlayerVoidEnergy) { return 0; }
