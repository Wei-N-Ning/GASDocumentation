// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Abilities/GDGameplayAbility.h"
#include "GDGA_CharacterJump.generated.h"

/**
 * Makes the Character try to jump using the standard Character->Jump. This is an example of a non-instanced ability.
 * See: https://github.com/tranek/GASDocumentation#467-instancing-policy
 *
 * instanced-per-actor:
 * This will probably be the Instancing Policy that you use the most. You can use it for any ability and provides persistence
 * between activations. The designer is responsible for manually resetting any variables between activations that need it.
 *
 * not-instanced
 * This has the best performance of the three but is the most restrictive in what can be done with it. Non-Instanced
 * GameplayAbilities cannot store state, meaning no dynamic variables and no binding to AbilityTask delegates. The best
 * place to use them is for frequently used simple abilities like minion basic attacks in a MOBA or RTS. The Sample
 * Project's Jump GameplayAbility is Non-Instanced.
 */
UCLASS()
class GASDOCUMENTATION_API UGDGA_CharacterJump : public UGDGameplayAbility
{
	GENERATED_BODY()

public:
	UGDGA_CharacterJump();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
};
