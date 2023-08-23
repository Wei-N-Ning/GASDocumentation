// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASDocumentation/GASDocumentation.h"
#include "GDGameplayAbility.generated.h"

/**
 * The ASC provides four other methods of activating GameplayAbilities:
 * by
 * GameplayTag,
 * GameplayAbility class,
 * GameplayAbilitySpec handle,
 * an event.
 * Activating a GameplayAbility by event allows you to pass in a payload of data with the event.
 *
*   UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateAbilitiesByTag(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation = true);

	bool TryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true);

	bool TriggerAbilityFromGameplayEvent(FGameplayAbilitySpecHandle AbilityToTrigger, FGameplayAbilityActorInfo* ActorInfo, FGameplayTag Tag, const FGameplayEventData* Payload, UAbilitySystemComponent& Component);

	FGameplayAbilitySpecHandle GiveAbilityAndActivateOnce(const FGameplayAbilitySpec& AbilitySpec, const FGameplayEventData* GameplayEventData);

 * Note: When activating a GameplayAbility from event in Blueprint, you must use the ActivateAbilityFromEvent node and
 * the standard ActivateAbility node cannot exist in your graph. If the ActivateAbility node exists, it will always be
 * called over the ActivateAbilityFromEvent node.
 * 
 */
UCLASS()
class GASDOCUMENTATION_API UGDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGDGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGDAbilityInputID AbilityInputID = EGDAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGDAbilityInputID AbilityID = EGDAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	// 
	// To implement passive GameplayAbilities that automatically activate and run continuously, override
	// UGameplayAbility::OnAvatarSet() which is automatically called when a GameplayAbility is granted and the AvatarActor
	// is set and call TryActivateAbility().
	//
	// I recommend adding a bool to your custom UGameplayAbility class specifying if the GameplayAbility should be activated
	// when granted. The Sample Project does this for its passive armor stacking ability.
	// (see the pass armor BP which subclasses this class and sets ActivateAbilityOnGranted to True)
	// Passive GameplayAbilities will typically have a Net Execution Policy of Server Only.
	//
	// Epic describes this function as the correct place to initiate passive abilities and to do BeginPlay type things.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	// GameplayAbilities come with functionality for optional costs and cooldowns. Costs are predefined amounts of Attributes
	// that the ASC must have in order to activate the GameplayAbility implemented with an Instant GameplayEffect (Cost GE).
	// Cooldowns are timers that prevent the reactivation of a GameplayAbility until it expires and is implemented with a
	// Duration GameplayEffect (Cooldown GE).

	// Before a GameplayAbility calls UGameplayAbility::Activate(), it calls UGameplayAbility::CanActivateAbility().
	// This function checks if the owning ASC can afford the cost (UGameplayAbility::CheckCost()) and ensures that the
	// GameplayAbility is not on cooldown (UGameplayAbility::CheckCooldown()).

	// After a GameplayAbility calls Activate(), it can optionally commit the cost and cooldown at any time using
	// UGameplayAbility::CommitAbility() which calls UGameplayAbility::CommitCost() and UGameplayAbility::CommitCooldown().
	// The designer may choose to call CommitCost() or CommitCooldown() separately if they shouldn't be committed at the
	// same time. Committing cost and cooldown calls CheckCost() and CheckCooldown() one more time and is the last chance
	// for the GameplayAbility to fail related to them. The owning ASC's Attributes could potentially change after a
	// GameplayAbility is activated, failing to meet the cost at time of commit. Committing the cost and cooldown can be
	// locally predicted if the prediction key is valid at the time of commit.

	// to observe the execution of CanActivateAbility, uncomment this function
	// virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
};
