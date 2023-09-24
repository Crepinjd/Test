// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Audio/Visualizers/MicrophoneVisualizer.h"
#include "MicrophoneVisualizer.h"


void UMicrophoneVisualizer::SetVisualizerWidth(float Width)
{
    VisualizerWidth = Width;
    SynchronizeProperties();
}

void UMicrophoneVisualizer::SetVisualizerHeight(float Height)
{
    VisualizerHeight = Height;
    SynchronizeProperties();
}

void UMicrophoneVisualizer::SetSpiritsMicrophone(ASpiritsMicrophone* InSpiritsMicrophone)
{
    SpiritsMicrophone = InSpiritsMicrophone; 
    SynchronizeProperties();
}


////////////////////////////////////////////////////

void UMicrophoneVisualizer::SetSpectralAnalysis(const TArray<FSoundSubmixSpectralAnalysisBandSettings> InBandSettings, float InUpdateRate, float InDecibelNoiseFloor, bool InDoNormalize, bool InDoAutoRange, float InAutoRangeAttackTime, float InAutoRangeReleaseTime)
{
   BandSettings = InBandSettings;
   UpdateRate = InUpdateRate;
   DecibelNoiseFloor = InDecibelNoiseFloor;
   bDoNormalize = InDoNormalize;
   bDoAutoRange = InDoAutoRange;
   AutoRangeAttackTime = InAutoRangeAttackTime;
   AutoRangeReleaseTime = InAutoRangeReleaseTime;
}

void UMicrophoneVisualizer::StartSpectralAnalysis(EFFTSize FFTSize, EFFTPeakInterpolationMethod InterpolationMethod, EFFTWindowType WindowType, float HopSize, EAudioSpectrumType SpectrumType)
{
    if (SpiritsMicrophone)
    {
        SpiritsMicrophone->Submix->AddSpectralAnalysisDelegate(GetWorld(), BandSettings, OnMagnitudesDataSend, UpdateRate, DecibelNoiseFloor, bDoNormalize, bDoAutoRange, AutoRangeAttackTime, AutoRangeReleaseTime);
        SpiritsMicrophone->Submix->StartSpectralAnalysis(GetWorld(), FFTSize, InterpolationMethod, WindowType, HopSize, SpectrumType);
    }   
}

void UMicrophoneVisualizer::StopSpectralAnalysis()
{
    if (SpiritsMicrophone)
    {
        SpiritsMicrophone->Submix->StopSpectralAnalysis(GetWorld());
        SpiritsMicrophone->Submix->RemoveSpectralAnalysisDelegate(GetWorld(), OnMagnitudesDataSend);
    }   
}


////////////////////////////////////////////////////

void UMicrophoneVisualizer::SynchronizeProperties()
{
    Super::SynchronizeProperties();    
    MicrophoneVisualizer->SetVisualizerWidth(VisualizerWidth);
    MicrophoneVisualizer->SetVisualizerHeight(VisualizerHeight);
    MicrophoneVisualizer->SetSpiritsMicrophone(SpiritsMicrophone);
}

void UMicrophoneVisualizer::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);
    MicrophoneVisualizer.Reset();
}

void UMicrophoneVisualizer::PostLoad()
{
    OnMagnitudesDataSend.BindUFunction(this, FName("OnSpectralAnalysis"));
}

////////////////////////////////////////

const FText UMicrophoneVisualizer::GetPaletteCategory()
{
    return FText::FromString("Unreal Spirits");
}

TSharedRef<SWidget> UMicrophoneVisualizer::RebuildWidget()
{   
    MicrophoneVisualizer = SNew(SMicrophoneVisualizer)
        .VisualizerWidth(VisualizerWidth)
        .VisualizerHeight(VisualizerHeight)
        .SpiritsMicrophone(SpiritsMicrophone);

    return MicrophoneVisualizer.ToSharedRef();
}

#if WITH_ACCESSIBILITY
TSharedPtr<SWidget> UMicrophoneVisualizer::GetAccessibleWidget() const
{
    return MicrophoneVisualizer;
}
#endif

void UMicrophoneVisualizer::OnSpectralAnalysis(TArray<float> Magnitudes)
{
    UE_LOG(LogTemp, Warning, TEXT("| UMicrophoneVisualizer::OnSpectralAnalysis() "));
    for (size_t i = 0; i < Magnitudes.Num(); i++)
    {
        MicrophoneVisualizer->SetVisualizerBarSize(i,Magnitudes[i]);
    }
}
