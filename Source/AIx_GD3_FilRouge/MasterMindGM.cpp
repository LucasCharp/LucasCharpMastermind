// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterMindGM.h"

// Sets default values
AMasterMindGM::AMasterMindGM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterMindGM::BeginPlay()
{
	Super::BeginPlay();

	CreateSolution();
	
}

// Called every frame
void AMasterMindGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FLinearColor AMasterMindGM::GetColor(uint8 ColorNumber)
{
	if(ColorNumber < Colors.Num())
	{
		return Colors[ColorNumber];
	}

	return FLinearColor::Black;
	
}


void AMasterMindGM::CreateSolution()
{
	Solution.SetNum(4);
	for(uint8 i = 0; i < 4; i++)
	{
		Solution[i] = FMath::RandRange(0,5);
	}
}

bool AMasterMindGM::CheckAnswer(TArray<uint8> Answer)
{
	bool result = true;
	uint8 GoodPlace = 0;
	uint8 WrongPlace = 0;
	TArray<bool> SolutionAllowed{true,true,true,true};
	TArray<bool> AnswersAllowed{true,true,true,true};
	TArray<uint8> AnswerState{0,0,0,0};
	for(uint8 i = 0; i < 4; i++)
	{
		UE_LOG(LogTemp,Warning,TEXT("First element: %d"), Solution[i]);
		if (Answer[i] == Solution[i])
		{
			SolutionAllowed[i] = false;
			AnswersAllowed[i] = false;
			AnswerState[i] = 2;
			GoodPlace++;
		}
		else
		{
			result = false;
		}
	}


	for (uint8 i = 0; i < 4; i++)
	{
		if (AnswersAllowed[i])
		{
			for (uint8 j = 0; j < 4; j++)
			{
				if (SolutionAllowed[j] && Answer[i] == Solution[j])
				{
					WrongPlace++;
					SolutionAllowed[j] = false;
					AnswerState[i] = 1;
					break;
				}
			}
		}
	}

	
	for (uint8 i = 0; i < 4; i++)
	{
		UMaterialInterface* BaseMaterial = RefRowSpheres[i]->GetMaterial(0);
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		UE_LOG(LogTemp,Warning,TEXT("First element: %d"), AnswerState[i]); //Juste pour voir dans le debug avant
		if (AnswerState[i] == 1)
		{
			DynMaterial->SetVectorParameterValue("Color", FLinearColor::Red);
			RefRowSpheres[i]->SetMaterial(0, DynMaterial);
		}
		if (AnswerState[i] == 2)
		{
			DynMaterial->SetVectorParameterValue("Color", FLinearColor::Green);
			RefRowSpheres[i]->SetMaterial(0, DynMaterial);
		}
	}
	return result;
}

