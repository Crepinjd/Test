// Fill out your copyright notice in the Description page of Project Settings.


#include "Slates/Audio/Visualizers/Bars/SVisualizerBar.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SBox.h"	
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Kismet/KismetMathLibrary.h"

void SVisualizerBar::Construct(const FArguments& InArgs)
{
	//MC_Button_Style = &FMC_Style::Get().GetWidgetStyle<FMC_Button_Style>("MC_Button_Style");

	//Visualizer SizeBox
	VisualizerBarWidth = InArgs._BarWidth;
	VisualizerBarHeight = InArgs._BarHeight;

	//Visualizer Bar Brush 
	//VisualizerBarBrush = &MC_Button_Style->BackgroundBrush;
	
	//Margin
	FMargin MargingVisualizer = FMargin(10);	
	//FMargin MargingBar = FMargin(2);
	
	//Initialize Visualizer Background Brush	
	SAssignNew(VisualizerBarPtr, SImage)		
		.Image(VisualizerBarBrush);
	
	/*
	//Visualizer Bar Container
	SAssignNew(VisualizerBarContainerPtr, SVerticalBox)
		.content
		[
			VisualizerBarPtr.ToSharedRef()
		];
	*/
	
	ChildSlot
		[
			SAssignNew(VisualizerSizeBoxPtr, SBox)
				.HAlign(InArgs._HAlign)
				.VAlign(InArgs._VAlign)
				.WidthOverride(VisualizerBarWidth.Get())
				.HeightOverride(VisualizerBarHeight.Get())
				[					
					VisualizerBarPtr.ToSharedRef()
				]
		];	
}

//////////////////////////////////////////////////////
//Configs

SVisualizerBar::SVisualizerBar()
{
}

void SVisualizerBar::SetVisualizerBarWidth(float Width)
{
	SetAttribute(VisualizerBarWidth, TAttribute<float>(Width), EInvalidateWidgetReason::Paint);
	VisualizerSizeBoxPtr->SetWidthOverride(Width);
}

void SVisualizerBar::SetVisualizerBarHeight(float Height)
{
	SetAttribute(VisualizerBarHeight, TAttribute<float>(Height), EInvalidateWidgetReason::Paint);
	VisualizerSizeBoxPtr->SetHeightOverride(Height);
}

void SVisualizerBar::SetVisualizerBarSize(float Size)
{
	float SizeLocal = Size * 10;
	float Finalsize = UKismetMathLibrary::MapRangeClamped(SizeLocal , 0.1f, 1.0f,1.0f, VisualizerBarHeight.Get());

	TAttribute<TOptional<FVector2D>> InDesiredSizeOverride;
	InDesiredSizeOverride.Set(FVector2D(VisualizerBarWidth.Get(), Finalsize));
	VisualizerBarPtr.Get()->SetDesiredSizeOverride(InDesiredSizeOverride);
}

//////////////////////////////////////////////////////

TSharedRef<FSlateAccessibleWidget> SVisualizerBar::CreateAccessibleWidget()
{
	return MakeShareable<FSlateAccessibleWidget>(new FSlateAccessibleButton(SharedThis(this)));
}

