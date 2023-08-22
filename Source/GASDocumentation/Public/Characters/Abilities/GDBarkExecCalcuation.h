// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "UObject/Object.h"
#include "GDBarkExecCalcuation.generated.h"

/**
 * 
 */
UCLASS()
class GASDOCUMENTATION_API UGDBarkExecCalcuation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UGDBarkExecCalcuation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
