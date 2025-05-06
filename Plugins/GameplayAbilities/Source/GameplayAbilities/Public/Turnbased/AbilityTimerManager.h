#pragma once
#include "TimerManager.h"

class UAbilitySystemComponent;

GAMEPLAYABILITIES_API DECLARE_LOG_CATEGORY_EXTERN(LogAbilitySystemTurnbased, Display, All)

struct FAbilityTimerContainer
{
public:
	int32 Turn = 0;
	TArray<FTimerHandle> TimerHandles;
};

class GAMEPLAYABILITIES_API FAbilityTimerManager: public FTimerManager
{
public:
	void TickTurn(UAbilitySystemComponent* AbilitySystemComponent, int Delta = 1);
	float GetAbilityTimerRemaining(UAbilitySystemComponent* AbilitySystemComponent, FTimerHandle& InHandle);
	
	void SetAbilityTimer(UAbilitySystemComponent* AbilitySystemComponent, FTimerHandle& InOutHandle, FTimerDelegate const& InDelegate, float InRate, bool bInLoop, float InFirstDelay = -1.f);
	void ClearAbilityTimer(UAbilitySystemComponent* AbilitySystemComponent, FTimerHandle& InHandle);
	void SetAbilityTimerForNextTick(FTimerDelegate const& InDelegate);
	void ClearAllAbilityTimerContainers();
	
private:
	FAbilityTimerContainer& GetAbilityTimerContainer(UAbilitySystemComponent* AbilitySystemComponent);
	void AddAbilityTimer(UAbilitySystemComponent* AbilitySystemComponent, const FTimerHandle& TimerHandle);
	void RemoveAbilityTimer(UAbilitySystemComponent* AbilitySystemComponent, const FTimerHandle& TimerHandle);

private:
	TMap<TWeakObjectPtr<UAbilitySystemComponent>, FAbilityTimerContainer> AbilityTimerContainers;
};
