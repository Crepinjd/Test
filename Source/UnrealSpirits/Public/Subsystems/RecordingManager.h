// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
//Delegate
#include "Delegates/Delegate.h" 
//Unreal Spirits
#include "Settings/Unreal_Spirits_Settings.h"
//Parents
#include "Subsystems/EngineSubsystem.h"
#include "RecordingManager.generated.h"

class UUnreal_Spirits_Settings;
class IFileManager;

#define AUDIO_FOLDER FString("/Audio")
#define VIDEO_FOLDER FString("/Video")
#define OTHER_FOLDER FString("/Other")

UCLASS()
class UNREALSPIRITS_API URecordingManager : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem
	virtual void Deinitialize() override;	
	//Init / Reload for the manager
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager", Meta = (CompactNodeTitle = "INIT / RELOAD MANAGER"))
		void ReloadManager();

private:

	////////////////////////////////////////////////////////////////////////
	// Developer Settings
	////////////////////////////////////////////////////////////////////////

	//Developer Settings
	const UUnreal_Spirits_Settings* Unreal_Spirits_Settings = nullptr;
		
	////////////////////////////////////////////////////////////////////////
	// Unreal_Spirits_Settings Folders
	////////////////////////////////////////////////////////////////////////

	FString UnrealSpiritsDataFolder;

public:

	// Init / Reload Unreal Spirits Settings
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|Settings", Meta = (CompactNodeTitle = "INIT / RELOAD JAR & SERVERS CONFIGS"))
		void ReloadUnrealSpiritsSettings();

	//////////////////////////////////
	// Unreal Spirits : Folder
	//////////////////////////////////
	
	//Check JAR Internal Path 
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|Folder")
		bool CheckUnrealSpiritsFolder();

	//Create JAR Internal Path 
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|Folder")
		bool CreateUnrealSpiritsFolder();

	//Get Unreal Spirits Folder
	UFUNCTION(BlueprintPure, Category = "Unreal Spirits|Recording Manager|Folder", Meta = (CompactNodeTitle = "Get Unreal Spirits Folder"))
		FString GetUnrealSpiritsFolder();

	/////////////////////////////////////
	// Unreal Spirits : Current Session
	/////////////////////////////////////

private:
		
	FString CurrentSessionFolder;
	
	FString CurrentSessionAudioFolder;	
	FString CurrentSessionVideoFolder;
	FString CurrentSessionOtherFolder;

public:
	
	
	//Init Session Folder
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|Current Session")
		bool InitCurrentSession(const FString SessionName);

	//Check Session Folder
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|Current Session")
		bool CheckCurrentSessionFolders();

	//Create Session Folder
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|Current Session")
		bool CreateCurrentSessionFolders();

	//Get Current Session Folder Path
	UFUNCTION(BlueprintPure, Category = "Unreal Spirits|Recording Manager|Current Session", Meta = (CompactNodeTitle = "Get Current Session Folder"))
		FString GetCurrentSessionFolder();

	//Get Current Session Audio Folder Path
	UFUNCTION(BlueprintPure, Category = "Unreal Spirits|Recording Manager|Current Session", Meta = (CompactNodeTitle = "Get Current Session Audio Folder"))
		FString GetCurrentSessionAudioFolder();

	//Get Current Session Video Folder Path
	UFUNCTION(BlueprintPure, Category = "Unreal Spirits|Recording Manager|Current Session", Meta = (CompactNodeTitle = "Get Current Session Video Folder"))
		FString GetCurrentSessionVideoFolder();

	//Get Current Session Other Folder Path
	UFUNCTION(BlueprintPure, Category = "Unreal Spirits|Recording Manager|Current Session", Meta = (CompactNodeTitle = "Get Current Session Other Folder"))
		FString GetCurrentSessionOtherFolder();


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	// Unreal Spirits : All Sessions
	////////////////////////////////////////////////////////////////////////

private: 

	//All Unreal Spirits Sessions List
	TArray<FString> UnrealSpiritsSessionsList;

	//Init JAR List by versions
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|All Sessions", Meta = (CompactNodeTitle = "Update All Unreal Spirits Sessions"))
		void UpdateAllUnrealSpiritsSessions();

	//Get Craftbukkit Versions List
	UFUNCTION(BlueprintCallable, Category = "Unreal Spirits|Recording Manager|All Sessions", Meta = (CompactNodeTitle = "Get All Unreal Spirits Sessions List"))
		TArray<FString> GetAllUnrealSpiritsSessionsList();


};
