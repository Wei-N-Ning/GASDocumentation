// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GDDamageExecCalculation.generated.h"

/**
 * GameplayEffectExecutionCalculations aka ExecutionCalculation, Execution (you will often see this term in the plugin's
 * source code), or ExecCalc are the most powerful way for GameplayEffects to make changes to an ASC.
 * Like ModifierMagnitudeCalculations, these can capture Attributes and optionally snapshot them. Unlike MMCs, these can
 * change more than one Attribute and essentially do anything else that the programmer wants. The downside to this power
 * and flexibility is that they can not be predicted and they must be implemented in C++.
 *
 * ExecutionCalculations can only be used with Instant and Periodic GameplayEffects.
 * Anything with the word 'Execute' in it typically refers to these two types of GameplayEffects.
 *
 * Snapshotting captures the Attribute when the GameplayEffectSpec is created whereas not snapshotting captures the Attribute
 * when the GameplayEffectSpec is applied. Capturing Attributes recalculates their CurrentValue from existing mods on the ASC.
 * This recalculation will not run PreAttributeChange() in the AbilitySet so any clamping must be done here again.
 *
 * For Local Predicted, Server Only, and Server Initiated GameplayAbilities, the ExecCalc only calls on the Server.
 *
 * Calculating damage received based on a complex formula reading from many attributes on the Source and the Target is the
 * most common example of an ExecCalc.
 */
UCLASS()
class GASDOCUMENTATION_API UGDDamageExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UGDDamageExecCalculation();

	// calculating damage that reads the value of damage from the GameplayEffectSpec's SetByCaller and then mitigates that
	// value based on the armor Attribute captured from the Target
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
