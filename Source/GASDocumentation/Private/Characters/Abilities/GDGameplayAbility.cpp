// Copyright 2020 Dan Kestranek.


#include "Characters/Abilities/GDGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"

UGDGameplayAbility::UGDGameplayAbility()
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// Default tags that block this ability from activating
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")));
}

void UGDGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilitySpec & Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	// See pass armor BP which subclasses this UGDGameplayAbility;
	// it sets ActivateAbilityOnGranted to True, therefore it's a passive ability granted on spawn.
	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

// bool UGDGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
// 	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
// 	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
// {
// 	auto val = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CanActivateAbility %s: %s"), *GetName(), val ? TEXT("true") : TEXT("false")));
// 	return val;
// }
