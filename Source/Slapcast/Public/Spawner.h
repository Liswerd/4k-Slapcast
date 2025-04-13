// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class SLAPCAST_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
    virtual void Tick(float DeltaTime) override;
        
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    FVector range;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    FVector origin;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float numToSpawn;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    bool spawnOnPlay;
    
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void Spawn(float numToSpawn);
    
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void Spawn(float numToSpawn, FVector origin, FVector range);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* SphereMesh;

};
