// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "Engine/EngineTypes.h"
#include "Framework/SlateDelegates.h"
#include "UObject/ObjectMacros.h"
#include "Input/Reply.h"
#include "Styling/SlateTypes.h"
//Unreal Spirits
#include "Audio/SpiritsMicrophone.h"
//MC
#include "Slates/Audio/Visualizers/SMicrophoneVisualizer.h"
//Style
#include "Styles/UnrealSpirits_Style.h"
//#include "Slates/Styles/Buttons/MC_Button_Style.h"
//Parents
#include "Components/Widget.h"
#include "MicrophoneVisualizer.generated.h"


//class SMC_Button;
//class USlateWidgetStyleAsset;

class ASpiritsMicrophone;

//Event On Infrasons Magnitudes Data Send
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMagnitudesDataSend, const TArray<float>&, Magnitudes);

/**
 * 
 */
UCLASS()
class UMicrophoneVisualizer : public UWidget
{
	GENERATED_BODY()

public:

	
	////////////////////////////////////////
	//Visualizer Size Box

	//Visualizer Width
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualizer|Apparence", Meta = (ExposeOnSpawn = true))
		float VisualizerWidth = 350.0f;
	//Visualizer Height	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualizer|Apparence", Meta = (ExposeOnSpawn = true))
		float VisualizerHeight = 80.0f;


	//Set Visualizer Width
	UFUNCTION(BlueprintCallable, Category = "Visualizer|Apparence")
		void SetVisualizerWidth(float Width);
	//Set Visualizer Height
	UFUNCTION(BlueprintCallable, Category = "Visualizer|Apparence")
		void SetVisualizerHeight(float Height);

	////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualizer|References", Meta = (ExposeOnSpawn = true))
		ASpiritsMicrophone* SpiritsMicrophone = nullptr;

	/**
	 * Set ASpiritsMicrophone Reference
	 */
	UFUNCTION(BlueprintCallable, Category = "Visualizer|References")
		void SetSpiritsMicrophone(ASpiritsMicrophone* InSpiritsMicrophone);

	////////////////////////////////////////



	////////////////////////////////////
	// Spectral Analysis 
	////////////////////////////////////
			

	// Called when the button is clicked
	UPROPERTY()	
	FOnSubmixSpectralAnalysisBP  OnMagnitudesDataSend;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		TArray<FSoundSubmixSpectralAnalysisBandSettings> BandSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		float UpdateRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		float DecibelNoiseFloor; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		bool bDoNormalize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		bool bDoAutoRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		float AutoRangeAttackTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spectrum", Meta = (ExposeOnSpawn = true))
		float AutoRangeReleaseTime;
	
	UFUNCTION(BlueprintCallable, Category = "Spectrum")
		void SetSpectralAnalysis(const TArray<FSoundSubmixSpectralAnalysisBandSettings> InBandSettings, float InUpdateRate, float InDecibelNoiseFloor, bool InDoNormalize, bool InDoAutoRange, float InAutoRangeAttackTime, float InAutoRangeReleaseTime);

	UFUNCTION(BlueprintCallable, Category = "Spectrum")
		void StartSpectralAnalysis(EFFTSize FFTSize = EFFTSize::Max, EFFTPeakInterpolationMethod InterpolationMethod = EFFTPeakInterpolationMethod::Linear, EFFTWindowType WindowType = EFFTWindowType::None, float HopSize = 0.0f, EAudioSpectrumType SpectrumType = EAudioSpectrumType::Decibel);

	UFUNCTION(BlueprintCallable, Category = "Spectrum")
		void StopSpectralAnalysis();



public:

	// UWidget interface
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
#if WITH_EDITOR
	virtual TSharedRef<SWidget> RebuildDesignWidget(TSharedRef<SWidget> Content) override { return Content; }
#endif
	//~ End UWidget Interface

#if WITH_ACCESSIBILITY
	virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;
#endif

protected:

	/** Native Slate Widget */
	TSharedPtr<SMicrophoneVisualizer> MicrophoneVisualizer = nullptr;
	
	void OnSpectralAnalysis(TArray<float> Magnitudes);

};
