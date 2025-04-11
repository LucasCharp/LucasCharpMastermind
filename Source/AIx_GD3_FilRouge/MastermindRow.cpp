// Fill out your copyright notice in the Description page of Project Settings.


#include "MastermindRow.h"

#include "MastermindSphere.h"

// Sets default values
AMastermindRow::AMastermindRow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMastermindRow::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AMastermindRow::SetRefForManager, // La fonction à appeler
		0.1f,                             // Le délai en secondes
		false                             // Ne pas répéter (false = une seule fois)
	);
}

// Called every frame
void AMastermindRow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMastermindRow::Clicked()
{
	TArray<uint8> Answer;
	Answer.SetNum(4);
	for(int i = 0; i < 4; i++)
	{
		Answer[i] = PlayerSpheres[i]->GetComponentByClass<UMastermindSphere>()->GetSphereColor();
	}
	Manager->CheckAnswer(Answer);
}

void AMastermindRow::SetRefForManager()
{
	Manager->RefRowSpheres.SetNum(4);
	for (uint8 i = 0; i < 4; i++)
	{
		Manager->RefRowSpheres[i] = RowSpheres[i];
	}
}

