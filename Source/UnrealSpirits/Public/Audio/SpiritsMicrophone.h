// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "Misc/Paths.h"
#include "Engine/EngineTypes.h"
//audio
#include "AudioDevice.h"
#include "AudioCaptureCore.h"
#include "AudioCapture.h"	
#include "AudioDevice.h"	
#include "AudioCaptureCore.h"
#include "AudioMixerBlueprintLibrary.h"
//Unreal Spirits
#include "Settings/Unreal_Spirits_Settings.h"
#include "Subsystems/RecordingManager.h"
//Parent
#include "GameFramework/Actor.h"
#include "SpiritsMicrophone.generated.h"

class FAudioDevice;
class UAudioCaptureComponent;
class UAudioGenerator;

class UAudioMixerBlueprintLibrary;
class UUnreal_Spirits_Settings;

/*
//Event On Infrasons Magnitudes Data Send
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfrasonsMagnitudesDataSend, TArray<float>, InfrasonsMagnitudes);

//Event On Audible Magnitudes Data Send
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudibleMagnitudesDataSend, TArray<float>, AudibleMagnitudes);

//Event On Audible Magnitudes Data Send
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltrasonsMagnitudesDataSend, TArray<float>, UltrasonsMagnitudes);



//Event On Envellopes Data Send
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnvellopesDataSend, TArray<float>, Envellopes);
*/

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Unreal Spirit|Audio")
class UNREALSPIRITS_API ASpiritsMicrophone : public AActor
{
	GENERATED_BODY()
	

public:

	ASpiritsMicrophone();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	// Called when the game End
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	virtual void Tick(float DeltaSeconds) override;

private:

	////////////////////////////////////
	// References
	////////////////////////////////////

	const UUnreal_Spirits_Settings* Unreal_Spirits_Settings = nullptr;
	
	URecordingManager* RecordingManager = nullptr;
		
	FString MicrophoneFolder;

	void InitMicrophoneFolder();

public:

	UFUNCTION(BlueprintPure, Category = "Recording", Meta = (CompactNodeTitle = "Get Microphone Folder"))
	FString GetMicrophoneFolder();

	////////////////////////////////////
	//Components
	////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composants Audio")
		UAudioCaptureComponent* AudioCaptureComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composants Audio")
		USoundSubmix* Submix = NewObject<USoundSubmix>();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composants Audio")
		USoundWave* SoundWave;

	////////////////////////////////////
	// Microphone Configs
	////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		FString Name = "My Microphone";		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		float Channels = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		float SampleRate = 48000.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		float SendVolume = 1.0f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		float RecordingVolume = 1.0f;

	////////////////////////////////////
	// Recording
	////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		EAudioRecordingExportType FileType;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		float Lenght = 60.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		int32 Divisions = 2;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording", Meta = (ExposeOnSpawn = true))
		float DivisionMaxLenght;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording")
		FTimerHandle TimerRecording;
			
	UFUNCTION(BlueprintCallable, Category = "Recording", Meta = (CompactNodeTitle = "Start Recording"))
		void StartRecording();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Recording", Meta = (CompactNodeTitle = "Start Recording"))
		void Recording();

		void Recording_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Recording", Meta = (CompactNodeTitle = "Finish Recording"))
		void FinishRecording();

		void FinishRecording_Implementation();


	UFUNCTION(BlueprintCallable, Category = "Recording", Meta = (CompactNodeTitle = "Stop Recording"))
		void StopRecording();

	////////////////////////////////////
	// Recording States
	////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		FString CurrentSaveName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		bool bRecording = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		int32 CurrentDivision = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		float CurrentDivisionTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
		float RecordingTime = 0.0f;

	//
	UFUNCTION(BlueprintCallable, Category = "Recording", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 3))
		void ResetRecordingStates();
	//
	UFUNCTION(BlueprintCallable, Category = "Recording", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = 3))
		void SetRecordingName();



};
