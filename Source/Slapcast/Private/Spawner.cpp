// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    SphereMesh->SetupAttachment(Mesh); // Attach SphereMesh to Mesh
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
    if (spawnOnPlay)
    {
        Spawn(numToSpawn, origin, range);
    }
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::Spawn(float numToSpawn){
    for(int i = 0; i < numToSpawn; ++i){
        FVector loc = GetActorLocation();
        
        UStaticMeshComponent* NewMesh = NewObject<UStaticMeshComponent>(this);
        if (NewMesh && Mesh && Mesh->GetStaticMesh())
        {
            NewMesh->SetStaticMesh(Mesh->GetStaticMesh());
            NewMesh->SetWorldLocation(loc);
            NewMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
            NewMesh->RegisterComponent();
        }
        /*
        AEnemyActor *enemy = GetWorld()->SpawnActor<AEnemyActor>(loc, FRotator::ZeroRotator);
         */
    }
}

void ASpawner::Spawn(float numToSpawn, FVector origin, FVector range) {
    for (int i = 0; i < numToSpawn; ++i) {
        FVector randLoc = FVector(
            FMath::RandRange(origin.X - range.X, origin.X + range.X),
            FMath::RandRange(origin.Y - range.Y, origin.Y + range.Y),
            FMath::RandRange(origin.Z - range.Z, origin.Z + range.Z)
        );

        // Clone the mesh and attach it to this actor
        UStaticMeshComponent* NewMesh = NewObject<UStaticMeshComponent>(this);
        if (NewMesh && Mesh && Mesh->GetStaticMesh())
        {
            NewMesh->SetStaticMesh(Mesh->GetStaticMesh());
            NewMesh->SetWorldLocation(randLoc);
            NewMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
            NewMesh->RegisterComponent();
        }
        /*
        AEnemyActor* enemy = GetWorld()->SpawnActor<AEnemyActor>(randLoc, FRotator::ZeroRotator);
         */
    }
}

