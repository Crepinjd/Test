// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSpirits.h"
#include "Styles/UnrealSpirits_Style.h"
//Ue5
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, UnrealSpirits, "UnrealSpirits" );

#define LOCTEXT_NAMESPACE "FUnrealSpiritsModule"

void FUnrealSpiritsModule::StartupModule()
{
	//////////////////////////////////////////////
	//FMC_Style
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	//FMC_Style Hot reload hack
	FSlateStyleRegistry::UnRegisterSlateStyle(FUnrealSpirits_Style::GetStyleSetName());
	FUnrealSpirits_Style::Initialize();
	//////////////////////////////////////////////
}

void FUnrealSpiritsModule::ShutdownModule()
{
	//////////////////////////////////////////////
	//FMC_Style
	FUnrealSpirits_Style::Shutdown();
	//////////////////////////////////////////////
}

#undef LOCTEXT_NAMESPACE
