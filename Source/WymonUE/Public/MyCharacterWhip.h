#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "MyCharacterWhip.generated.h

UCLASS()
class WymonUE AMyCharacterWhip : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacterWhip();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UBoxComponent* WhipCollision;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float WhipDamage = 25.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float WhipRange = 200.0f;
    
    bool bIsAttacking = false;

public:
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void WhipAttack();
    
    UFUNCTION()
    void OnWhipHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

private:
    void EnableWhipCollision();
    void DisableWhipCollision();
};