// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/Unreal_Spirits_Settings.h"

UUnreal_Spirits_Settings::UUnreal_Spirits_Settings(const FObjectInitializer& ObjectInitializer)
{

}

FName UUnreal_Spirits_Settings::GetCategoryName() const
{
	return "Project";
}

FText UUnreal_Spirits_Settings::GetSectionText() const
{
	return FText::FromString("Unreal Spirits - Developer Settings");
}

FText UUnreal_Spirits_Settings::GetSectionDescription() const
{
	return FText::FromString("Unreal Spirits - Developer Settings for the apllication");
}
