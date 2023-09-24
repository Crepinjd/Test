// Fill out your copyright notice in the Description page of Project Settings.


#include "Slates/Audio/Visualizers/SMicrophoneVisualizer.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

SMicrophoneVisualizer::SMicrophoneVisualizer()
{

}

void SMicrophoneVisualizer::Construct(const FArguments& InArgs)
{
	//MC_Button_Style = &FMC_Style::Get().GetWidgetStyle<FMC_Button_Style>("MC_Button_Style");

	//Visualizer SizeBox
	VisualizerWidth = InArgs._VisualizerWidth;
	VisualizerHeight = InArgs._VisualizerHeight;

	//Visualizer Background Brush	
	//VisualizerBackgroundBrush = &MC_Button_Style->BackgroundBrush;
	
	NumberOfBars = InArgs._NumberOfBars;

	//Margin
	FMargin MargingVisualizer = FMargin(10);	
	//FMargin MargingBar = FMargin(2);
	
	//Initialize Visualizer Background Brush	
	SAssignNew(VisualizerBackgroundPtr, SImage)
		.Image(VisualizerBackgroundBrush);
	
	//Initialize Visualizer Container 
	SAssignNew(VisualizerContainerPtr, SUniformGridPanel);
	
	ChildSlot
		[
			SAssignNew(VisualizerSizeBoxPtr, SBox)
				.HAlign(InArgs._HAlign)
				.VAlign(InArgs._VAlign)
				.WidthOverride(VisualizerWidth.Get())
				.HeightOverride(VisualizerHeight.Get())
				[
					SNew(SOverlay)
						+ SOverlay::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							VisualizerBackgroundPtr.ToSharedRef()
						]					
						+ SOverlay::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)	
						.Padding(MargingVisualizer)
						[
							VisualizerContainerPtr.ToSharedRef()
						]
				]
		];	
}

//////////////////////////////////////////////////////
//Configs

void SMicrophoneVisualizer::SetVisualizerWidth(float Width)
{
	SetAttribute(VisualizerWidth, TAttribute<float>(Width), EInvalidateWidgetReason::Paint);
	VisualizerSizeBoxPtr->SetWidthOverride(Width);
}

void SMicrophoneVisualizer::SetVisualizerHeight(float Height)
{
	SetAttribute(VisualizerHeight, TAttribute<float>(Height), EInvalidateWidgetReason::Paint);
	VisualizerSizeBoxPtr->SetHeightOverride(Height);
}

void SMicrophoneVisualizer::SetBackgroundBrush(const FSlateBrush* Brush)
{
	SetAttribute(VisualizerBackgroundBrush, TAttribute<const FSlateBrush*>(Brush), EInvalidateWidgetReason::Paint);
}

void SMicrophoneVisualizer::SetSpiritsMicrophone(const ASpiritsMicrophone* InSpiritsMicrophone)
{
	//SetAttribute(SpiritsMicrophone, TAttribute<const ASpiritsMicrophone*>(&InSpiritsMicrophone), EInvalidateWidgetReason::Paint);
	SpiritsMicrophone = InSpiritsMicrophone;
}

void SMicrophoneVisualizer::SetVisualizerBarSize(int32 Index, float Size)
{
	VisualizerBars[Index] SetVisualizerBarSize(Size);
	//VisualizerBars[Index].Get()->SetVisualizerBarSize(Size);
	VisualizerContainerPtr.Get().chil ParentWidget(SVisualizerBar)
}


//////////////////////////////////////////////////////

int32 SMicrophoneVisualizer::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{	
	VisualizerBars->Empty();

	for (size_t i = 0; i < NumberOfBars.Get() - 1; i++)
	{
		TSharedPtr<SVisualizerBar> NewBar =
			SAssignNew(NewBar, SVisualizerBar)
			.BarWidth(VisualizerWidth.Get() - 20 / NumberOfBars.Get())
			.BarHeight(VisualizerHeight.Get() - 20);
		
		VisualizerContainerPtr.Get()->AddSlot(i, 0);
		//(NewBar.ToSharedRef());
		
		VisualizerBars->Add(NewBar.ToSharedRef());
	}
	return LayerId;




	// we draw the slider like a horizontal slider regardless of the orientation, and apply a render transform to make it display correctly.
	// However, the AllottedGeometry is computed as it will be rendered, so we have to use the "horizontal orientation" when doing drawing computations.
	/*
	const float AllottedWidth = Orientation == Orient_Horizontal ? AllottedGeometry.GetLocalSize().X : AllottedGeometry.GetLocalSize().Y;
	const float AllottedHeight = Orientation == Orient_Horizontal ? AllottedGeometry.GetLocalSize().Y : AllottedGeometry.GetLocalSize().X;

	float HandleRotation;
	FVector2f HandleTopLeftPoint;
	FVector2f SliderStartPoint;
	FVector2f SliderEndPoint;

	// calculate slider geometry as if it's a horizontal slider (we'll rotate it later if it's vertical)
	const FVector2f HandleSize = GetThumbImage()->ImageSize;
	const FVector2f HalfHandleSize = 0.5f * HandleSize;
	const float Indentation = IndentHandleSlateAttribute.Get() ? HandleSize.X : 0.0f;

	// We clamp to make sure that the slider cannot go out of the slider Length.
	const float SliderPercent = FMath::Clamp(GetNormalizedValue(), 0.0f, 1.0f);
	const float SliderLength = AllottedWidth - (Indentation + HandleSize.X);
	const float SliderHandleOffset = SliderPercent * SliderLength;
	const float SliderY = 0.5f * AllottedHeight;

	HandleRotation = 0.0f;
	HandleTopLeftPoint = FVector2f(SliderHandleOffset + (0.5f * Indentation), SliderY - HalfHandleSize.Y);

	SliderStartPoint = FVector2f(HalfHandleSize.X, SliderY);
	SliderEndPoint = FVector2f(AllottedWidth - HalfHandleSize.X, SliderY);

	FGeometry SliderGeometry = AllottedGeometry;

	// rotate the slider 90deg if it's vertical. The 0 side goes on the bottom, the 1 side on the top.
	if (Orientation == Orient_Vertical)
	{
		// Do this by translating along -X by the width of the geometry, then rotating 90 degreess CCW (left-hand coords)
		FSlateRenderTransform SlateRenderTransform = TransformCast<FSlateRenderTransform>(Concatenate(Inverse(FVector2f(AllottedWidth, 0)), FQuat2D(FMath::DegreesToRadians(-90.0f))));
		// create a child geometry matching this one, but with the render transform.
		SliderGeometry = AllottedGeometry.MakeChild(
			FVector2f(AllottedWidth, AllottedHeight),
			FSlateLayoutTransform(),
			SlateRenderTransform, FVector2f::ZeroVector);
	}

	const bool bEnabled = ShouldBeEnabled(bParentEnabled);
	const ESlateDrawEffect DrawEffects = bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	// draw slider bar
	auto BarTopLeft = FVector2f(SliderStartPoint.X, SliderStartPoint.Y - Style->BarThickness * 0.5f);
	auto BarSize = FVector2f(SliderEndPoint.X - SliderStartPoint.X, Style->BarThickness);
	auto BarImage = GetBarImage();
	auto ThumbImage = GetThumbImage();
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		SliderGeometry.ToPaintGeometry(BarSize, FSlateLayoutTransform(BarTopLeft)),
		BarImage,
		DrawEffects,
		BarImage->GetTint(InWidgetStyle) * SliderBarColorSlateAttribute.Get().GetColor(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint()
	);

	++LayerId;

	// draw slider thumb
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		SliderGeometry.ToPaintGeometry(GetThumbImage()->ImageSize, FSlateLayoutTransform(HandleTopLeftPoint)),
		ThumbImage,
		DrawEffects,
		ThumbImage->GetTint(InWidgetStyle) * SliderHandleColorSlateAttribute.Get().GetColor(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint()
	);
	return LayerId;
	*/
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, true);//bEnabled
}
