#include "MyCharacterWhip.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// CONSTRUCTOR - Put collision setup inside here
AMyCharacterWhip::AMyCharacterWhip()
{
    // Set this character to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // WHIP COLLISION SETUP GOES INSIDE THE CONSTRUCTOR:
    WhipCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WhipCollision"));
    WhipCollision->SetupAttachment(RootComponent);
    WhipCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WhipCollision->SetCollisionProfileName("Trigger");
    WhipCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterWhip::OnWhipHit);

    // Position the collision box in front of character
    WhipCollision->SetRelativeLocation(FVector(WhipRange * 0.5f, 0.0f, 0.0f));
    WhipCollision->SetBoxExtent(FVector(WhipRange * 0.5f, 50.0f, 100.0f));
}

// BeginPlay function
void AMyCharacterWhip::BeginPlay()
{
    Super::BeginPlay();
    // Any initialization code that needs to run when the game starts
}

// Input setup function
void AMyCharacterWhip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAction("WhipAttack", IE_Pressed, this, &AMyCharacterWhip::WhipAttack);
}

// Whip attack function
void AMyCharacterWhip::WhipAttack()
{
    if (bIsAttacking) return;
    
    bIsAttacking = true;
    UE_LOG(LogTemp, Warning, TEXT("Whip Attack!"));
    
    // Enable collision after a short delay (or use animation notify)
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyCharacterWhip::EnableWhipCollision, 0.2f, false);
}

// Enable whip collision
void AMyCharacterWhip::EnableWhipCollision()
{
    if (WhipCollision)
    {
        WhipCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        
        // Disable after short duration
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyCharacterWhip::DisableWhipCollision, 0.3f, false);
    }
}

// Disable whip collision
void AMyCharacterWhip::DisableWhipCollision()
{
    if (WhipCollision)
    {
        WhipCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        bIsAttacking = false;
    }
}

// Handle whip hitting something
void AMyCharacterWhip::OnWhipHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Whip hit: %s"), *OtherActor->GetName());
        
        // Add damage logic here when you have enemies
        // Example:
        // if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
        // {
        //     Enemy->TakeDamage(WhipDamage);
        // }
    }
}