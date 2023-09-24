// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Interfaces/IPluginManager.h"
/**
 * 
 */
class FUnrealSpirits_Style
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();	

private:

	static TSharedPtr<class FSlateStyleSet> FUnrealSpirits_StyleInstance;

	static TSharedRef<class FSlateStyleSet> Create();

};