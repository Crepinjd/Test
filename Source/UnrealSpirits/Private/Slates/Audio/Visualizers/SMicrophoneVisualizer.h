// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Layout/Margin.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SUniformGridPanel.h"
//Unreal Spirits
#include "Audio/SpiritsMicrophone.h"
#include "Slates/Audio/Visualizers/Bars/SVisualizerBar.h"
#include "Styles/UnrealSpirits_Style.h"
#include "Slates/SUnreal_Spirits_Slates.h"

/*
* 
class ASpiritsMicrophone;
class FPaintArgs;
class FSlateWindowElementList;
enum class ETextFlowDirection : uint8;
enum class ETextShapingMethod : uint8;
*/

/**
 * 
 */
class SMicrophoneVisualizer : public SUnreal_Spirits_Slates
{
	//SLATE_DECLARE_WIDGET(SMicrophoneVisualizer, SUnreal_Spirits_Slates)

public:

	SLATE_BEGIN_ARGS(SMicrophoneVisualizer)
		: _HAlign(HAlign_Fill)
		, _VAlign(VAlign_Fill)
		, _VisualizerWidth(1020.0f)
		, _VisualizerHeight(120.0f)		
		, _SpiritsMicrophone(nullptr) 
		, _NumberOfBars(27)
		{
			
		}	

		/////////////////////////////////////////
		// Size Box

		/** Horizontal alignment */
		SLATE_ARGUMENT(EHorizontalAlignment, HAlign)
		/** Vertical alignment */
		SLATE_ARGUMENT(EVerticalAlignment, VAlign)
		
		//Visualizer Size Box
		SLATE_ATTRIBUTE(float, VisualizerWidth)
		SLATE_ATTRIBUTE(float, VisualizerHeight)
		
		/////////////////////////////////////////
		// Visualizer Spirits Microphone reference

		SLATE_ATTRIBUTE(ASpiritsMicrophone*, SpiritsMicrophone)

		SLATE_ATTRIBUTE(int32, NumberOfBars)


	SLATE_END_ARGS()
 
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	SMicrophoneVisualizer();

	//Button Size
	void SetVisualizerWidth(float Width);
	void SetVisualizerHeight(float Height);

	void SetBackgroundBrush(const FSlateBrush* Brush);

	//Set Spirits Microphone
	void SetSpiritsMicrophone(const ASpiritsMicrophone* InSpiritsMicrophone);
	
	int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;
	
	//TArray<TSharedPtr<SVisualizerBar>>* VisualizerBars;
	TArray<SVisualizerBar>* VisualizerBars;
	
	//TArray<UVisualizerBar> VisualizerBars;


	void SetVisualizerBarSize(int32 Index, float Size);

private:

	//Style 
	//const FMC_Button_Style* MC_Button_Style;
	
	//Visualizer SizeBox
	TSharedPtr<SBox> VisualizerSizeBoxPtr;
	TAttribute<float> VisualizerWidth;
	TAttribute<float> VisualizerHeight;


	//Visualizer Background
	TSharedPtr<SImage> VisualizerBackgroundPtr;
	TAttribute<const FSlateBrush*> VisualizerBackgroundBrush;
	
	// Visualizer Container 
	TSharedPtr<SUniformGridPanel> VisualizerContainerPtr;

	// Visualizer Spirits Microphone reference
	const ASpiritsMicrophone* SpiritsMicrophone = nullptr;

	TAttribute<int32> NumberOfBars;

	
};
