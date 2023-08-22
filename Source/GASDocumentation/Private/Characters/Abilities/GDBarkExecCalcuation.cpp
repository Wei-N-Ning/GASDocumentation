// Copyright 2023 Dan Kestranek.


#include "Characters/Abilities/GDBarkExecCalcuation.h"


UGDBarkExecCalcuation::UGDBarkExecCalcuation()
{
}


void UGDBarkExecCalcuation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("UGDBarkExecCalcuation::UGDBarkExecCalcuation()"));
}
