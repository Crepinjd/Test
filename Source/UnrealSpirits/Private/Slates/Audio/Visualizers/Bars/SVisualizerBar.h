// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Styling/SlateColor.h"
#include "Layout/Margin.h"
#include "Sound/SlateSound.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Framework/SlateDelegates.h"
#include "Styling/SlateWidgetStyleAsset.h"
#include "Widgets/Layout/SBorder.h"
//Unreal Spirits
#include "Audio/SpiritsMicrophone.h"
#include "Slates/SUnreal_Spirits_Slates.h"
//Style
#include "Styles/UnrealSpirits_Style.h"

//Styles Slate
#include "Styling/ISlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateWidgetStyleAsset.h"

/*
class ASpiritsMicrophone;
class FPaintArgs;
class FSlateWindowElementList;
enum class ETextFlowDirection : uint8;
enum class ETextShapingMethod : uint8;
*/

/**
 * 
 */
class SVisualizerBar: public SUnreal_Spirits_Slates
{	
public:
	SLATE_BEGIN_ARGS(SVisualizerBar)
		: _HAlign(HAlign_Fill)
		, _VAlign(VAlign_Bottom)
		, _BarWidth(1020.0f)
		, _BarHeight(120.0f)
		{
			
		}	

		/////////////////////////////////////////
		// Size Box

		/** Horizontal alignment */
		SLATE_ARGUMENT(EHorizontalAlignment, HAlign)
		/** Vertical alignment */
		SLATE_ARGUMENT(EVerticalAlignment, VAlign)
		
		//Visualizer Size Box
		SLATE_ATTRIBUTE(float, BarWidth)
		SLATE_ATTRIBUTE(float, BarHeight)
				

	SLATE_END_ARGS()
 
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	SVisualizerBar();

	//Button Size
	void SetVisualizerBarWidth(float Width);
	void SetVisualizerBarHeight(float Height);


	void SetVisualizerBarSize(float Size);


#if WITH_ACCESSIBILITY
	virtual TSharedRef<FSlateAccessibleWidget> CreateAccessibleWidget() override;
#endif

private:

	//Style 
	//const FMC_Button_Style* MC_Button_Style;
	
	//Visualizer SizeBox
	TSharedPtr<SBox> VisualizerSizeBoxPtr;
	TAttribute<float> VisualizerBarWidth;
	TAttribute<float> VisualizerBarHeight;
	
	// Visualizer Container 
	//TSharedPtr<SVerticalBox> VisualizerBarContainerPtr;

	//Visualizer Background
	TSharedPtr<SImage> VisualizerBarPtr;
	TAttribute<const FSlateBrush*> VisualizerBarBrush;
	
};
