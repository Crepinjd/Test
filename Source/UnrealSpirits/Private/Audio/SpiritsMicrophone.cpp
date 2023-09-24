// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/SpiritsMicrophone.h"
#include "AudioDevice.h"
#include "AudioMixerDevice.h"
#include "AudioDeviceManager.h"
#include "Sound/SoundSubmix.h"
#include "AudioCaptureComponent.h"
#include "AudioCapture.h"
#include "Sound/SampleBufferIO.h"
#include "Generators/AudioGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/FileManager.h"	

ASpiritsMicrophone::ASpiritsMicrophone()
{ 
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Dev Settings
	Unreal_Spirits_Settings = GetDefault<UUnreal_Spirits_Settings>();

}

void ASpiritsMicrophone::BeginPlay()
{
	Super::BeginPlay(); 

	RecordingManager = GEngine->GetEngineSubsystem<URecordingManager>();
	if (!RecordingManager)
	{
		UE_LOG(LogTemp, Error, TEXT("| ---------------------------------------------------------"));
		UE_LOG(LogTemp, Error, TEXT("| ASpiritsMicrophone : URecordingManager Not Find !"));
		UE_LOG(LogTemp, Error, TEXT("| ---------------------------------------------------------"));
	}

	if (RecordingManager && Unreal_Spirits_Settings)
	{
		//Set Microphone folder
		MicrophoneFolder = RecordingManager->GetCurrentSessionAudioFolder() + "/" + Name;

		if (!IFileManager::Get().DirectoryExists((TCHAR*)*GetMicrophoneFolder()))
		{
			if (IFileManager::Get().MakeDirectory((TCHAR*)*GetMicrophoneFolder()))
			{
				UE_LOG(LogTemp, Warning, TEXT("| ASpiritsMicrophone : Microphone Folder Created !"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("| ASpiritsMicrophone : Microphone Folder Already Present !"));
		}

		//Set Submix
		Submix = NewObject<USoundSubmix>();

		//Volume
		Submix->SetSubmixOutputVolume(this, RecordingVolume);
		//
		//

		AudioCaptureComponent = Cast<UAudioCaptureComponent>(AddComponentByClass(UAudioCaptureComponent::StaticClass(), false, FTransform::Identity, false));
		AudioCaptureComponent->SetSubmixSend(Submix, SendVolume);
		AudioCaptureComponent->Start();
	}
}

void ASpiritsMicrophone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AudioCaptureComponent->Stop();
}

void ASpiritsMicrophone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

////////////////////////////////////
// References
////////////////////////////////////

void ASpiritsMicrophone::InitMicrophoneFolder()
{
	MicrophoneFolder = RecordingManager->GetCurrentSessionAudioFolder() + "/" + Name;	
	UE_LOG(LogTemp, Display, TEXT("|  ASpiritsMicrophone : Init Microphone Folder : %s"), *MicrophoneFolder);
}

FString ASpiritsMicrophone::GetMicrophoneFolder()
{
	return MicrophoneFolder;
}

////////////////////////////////////
// Recording
////////////////////////////////////

void ASpiritsMicrophone::StartRecording()
{			
	ResetRecordingStates();
	//Timer
	GetWorld()->GetTimerManager().SetTimer(TimerRecording, this, &ASpiritsMicrophone::Recording_Implementation, 0.1f, true);
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerRecording))
	{
		UE_LOG(LogTemp, Display, TEXT("| ASpiritsMicrophone  : Timer Recording Start !"));
		//Set Recording Name
		SetRecordingName();		
		//Mixer Reference
		Audio::FMixerDevice* MixerDevice = FAudioDeviceManager::GetAudioMixerDeviceFromWorldContext(GetWorld());
		MixerDevice->RegisterSoundSubmix(Submix);
		MixerDevice->StartRecording(Submix, 0);
		//Set recording
		bRecording = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("| ASpiritsMicrophone  : Timer Recording Not Started !"));
	}
}

void ASpiritsMicrophone::Recording_Implementation()
{
	if (RecordingTime >= Lenght)
	{
		StopRecording();
	}
	else
	{		
		if (CurrentDivisionTime >= DivisionMaxLenght)
		{
			FinishRecording_Implementation();
			CurrentDivision = CurrentDivision + 1;
			CurrentDivisionTime = 0.0f;
			//Set Recording Name
			SetRecordingName();
			//Mixer Reference
			Audio::FMixerDevice* MixerDevice = FAudioDeviceManager::GetAudioMixerDeviceFromWorldContext(GetWorld());
			MixerDevice->RegisterSoundSubmix(Submix);
			MixerDevice->StartRecording(Submix, 0);
		}
		RecordingTime = RecordingTime + 0.1f;
	}
}

void ASpiritsMicrophone::FinishRecording_Implementation()
{
	UAudioMixerBlueprintLibrary::StopRecordingOutput(GetWorld(), FileType, CurrentSaveName, MicrophoneFolder, Submix, nullptr);
}

void ASpiritsMicrophone::StopRecording()
{
	//Check Recording
	if (bRecording)
	{
		FinishRecording_Implementation();
	}
	//Stop Timer
	GetWorld()->GetTimerManager().ClearTimer(TimerRecording);
	bRecording = false;
	//Reset Recording States
	ResetRecordingStates();
}

////////////////////////////////////
// Recording States
////////////////////////////////////

void ASpiritsMicrophone::ResetRecordingStates()
{
	DivisionMaxLenght = Lenght / Divisions;
	bRecording = false;
	CurrentDivision = 0;
	CurrentDivisionTime = 0.0f;
	RecordingTime = 0.0f;
	CurrentSaveName = "";
}

void ASpiritsMicrophone::SetRecordingName()
{
	//Set Current name for save
	FString Date = FString::FromInt(FDateTime::Now().GetHour());
	Date += ":" + FString::FromInt(FDateTime::Now().GetMinute());
	Date += ":" + FString::FromInt(FDateTime::Now().GetSecond());
	CurrentSaveName = Name + "-" + FString::FromInt(CurrentDivision) + "-" + Date;
}
