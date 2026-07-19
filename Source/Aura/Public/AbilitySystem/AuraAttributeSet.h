#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties(){}
	
	UPROPERTY(BlueprintReadWrite)
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY(BlueprintReadWrite)
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY(BlueprintReadWrite)
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	AController* SourceController = nullptr;
	UPROPERTY(BlueprintReadWrite)
	AController* TargetController = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	ACharacter* SourceCharacter = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ACharacter* TargetCharacter = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY(BlueprintReadWrite)
	UAbilitySystemComponent* TargetASC = nullptr;
	
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:	
	UAuraAttributeSet(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& GameplayAttribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData&) override;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
private:
	
	static void SetEffectProperties(const FGameplayEffectModCallbackData&, FEffectProperties& Properties);
};
