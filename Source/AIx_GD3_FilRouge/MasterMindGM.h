// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterMindGM.generated.h"
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSolutionChecked, uint8, uint8);

UCLASS()
class AIX_GD3_FILROUGE_API AMasterMindGM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterMindGM();



	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Settings")
	TArray<FLinearColor> Colors {FLinearColor::Red,FLinearColor::Yellow,FLinearColor::Green,FLinearColor::Blue,FLinearColor::Gray,FLinearColor::White};

	UPROPERTY(EditAnywhere)
	TArray<uint8> Solution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> RefRowSpheres;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	FLinearColor GetColor(uint8 ColorNumber);
	
	UFUNCTION()
	void CreateSolution();
	UFUNCTION(BlueprintCallable)
	bool CheckAnswer(TArray<uint8> Answer);
};
