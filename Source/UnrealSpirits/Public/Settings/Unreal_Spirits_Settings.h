// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Unreal_Spirits_Settings.generated.h"

/**
 * 
 */
UCLASS(Config = Unreal_Spirits_Settings, Defaultconfig, meta = (DisplayName = "Unreal Spirits - Developer Settings"))
class UNREALSPIRITS_API UUnreal_Spirits_Settings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UUnreal_Spirits_Settings(const FObjectInitializer& ObjectInitializer);

	virtual FName GetCategoryName() const override;

#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif

	//////////////////////////////////////////////////////////////////
	// Unreal Spirits Folders Settings
	//////////////////////////////////////////////////////////////////
	
	// General Folder Name
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Folders")
		FString GeneralFolderName = "MyUnrealSpiritsData";
	// Use External Folder
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Folders")
		bool bUseExternalFolder = false;
	// External Folder Path
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Folders")
		FString ExternalFolderPath = "C:/";
	
	//////////////////////////////////////////////////////////////////
	// Unreal Spirits Session Settings
	//////////////////////////////////////////////////////////////////

	// Session Name Default
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Session")
		FString SessionName = "MyUnrealSpiritsSession";


	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Session")
		int32 SessionPort;




};
