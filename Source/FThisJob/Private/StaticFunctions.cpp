// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticFunctions.h"

void UStaticFunctions::OrderByDistance(AActor* PlayerActor, TArray<AActor*> inArray, TArray<AActor*>& outArray){

	inArray.Sort([PlayerActor](const AActor& A,const AActor& B){
		float DistA = A.GetDistanceTo(PlayerActor);
		float DistB = B.GetDistanceTo(PlayerActor);
		return DistA > DistB;
	});
	outArray = inArray;
}

bool UStaticFunctions::IsInBuild()
{
#if WITH_EDITOR
	return  false;
#else
	return true;
#endif
}