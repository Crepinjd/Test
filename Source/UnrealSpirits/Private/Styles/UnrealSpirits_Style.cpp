// Fill out your copyright notice in the Description page of Project Settings.

#include "Styles/UnrealSpirits_Style.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FUnrealSpirits_Style::FUnrealSpirits_StyleInstance = NULL;

void FUnrealSpirits_Style::Initialize()
{
	if (!FUnrealSpirits_StyleInstance.IsValid())
	{
		FUnrealSpirits_StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*FUnrealSpirits_StyleInstance);
	}
}

void FUnrealSpirits_Style::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*FUnrealSpirits_StyleInstance);
	ensure(FUnrealSpirits_StyleInstance.IsUnique());
	FUnrealSpirits_StyleInstance.Reset();
}

void FUnrealSpirits_Style::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FUnrealSpirits_Style::Get()
{
	return *FUnrealSpirits_StyleInstance;
}

FName FUnrealSpirits_Style::GetStyleSetName()
{
	static FName StyleSetName(TEXT("FUnrealSpirits_Style"));
	return StyleSetName;
}

//#define PLUGIN_PATH(FMyStyle::)
//#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::ProjectPluginsDir()/ "MinecraftCore"/ "Content"/ "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
//#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::ProjectPluginsDir()/ "hMinecraftCore"/ "Content"/ "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
//#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::ProjectPluginsDir()/ "MinecraftCore"/ "Content"/ "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
//#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectPluginsDir()/ "MinecraftCore"/ "Content"/ "Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
//#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectPluginsDir()/ "MinecraftCore"/ "Content"/ "Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )

//#define PLUGIN_PATH(FMyStyle::)
#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::ProjectDir()/ "Content"/ "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::ProjectDir()/  "Content"/ "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::ProjectDir()/ "Content"/ "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectDir()/ "Content"/ "Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectDir()/ "Content"/ "Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )



TSharedRef<class FSlateStyleSet> FUnrealSpirits_Style::Create()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// !!! ATTENTION NE PAS SUPPRIMER CE FICHIER , il est relier au module du plugin qui recharge automatiquement
	// les styles par default au redemarrage du plugin et regroupe Tout les fichiers style du plugin cree dans l'editeur
	// Dans le dossier content du plugin ! Content/Slate/Styles
	// Pour les utiliser dans les Slates
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Path Slate/Styles du plugin
	//FString DossierStyles = FPaths::ProjectPluginsDir();
	//DossierStyles += "/Content/Slates/Styles";

	FString DossierStyles = "/Slate/Styles";

	UE_LOG(LogTemp, Warning, TEXT("| FUnrealSpirits_Style : Slates Path :  %s"), *DossierStyles);

	//Recuperation des styles cree dans l'editeur dans le Dossiers  Plugin=>Slate/Styles
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FUnrealSpirits_Style::GetStyleSetName(), DossierStyles, DossierStyles);
	FSlateStyleSet& Style = StyleRef.Get();

	//Assets
	//Style.Set("MinecraftCore.Background", new IMAGE_BRUSH("Asset/Minecraft_Background", FVector2D(32.0f, 32.0f)));
	//Style.Set("MinecraftCore.Button", new IMAGE_BRUSH("Asset/Minecraft_Button", FVector2D(350.0f, 40.0f)));
	//Style.Set("MinecraftCore.ButtonBackground", new IMAGE_BRUSH("Asset/FondButtonWhite", FVector2D(350.0f, 40.0f)));

	/*
	//MC Button Menu Texte Font
	Style.Set("MinecraftCore.ButtonMenuTextFont", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Minecraftia-Regular_Font", 18))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);	
	*/
	return StyleRef;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT
