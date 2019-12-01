// Fill out your copyright notice in the Description page of Project Settings.


#include "ManClick.h"


AManClick::AManClick()
{
	ClickedMesh=CreateDefaultSubobject<UStaticMeshComponent>("ClickedMesh");
	RootComponent = Cast<USceneComponent>(ClickedMesh);
}
