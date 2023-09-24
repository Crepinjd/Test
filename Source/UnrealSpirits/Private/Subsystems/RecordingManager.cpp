// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/RecordingManager.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"	

void URecordingManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	/*
	UE_LOG(LogTemp, Display, TEXT("| ProjectDir            : %s "), *FPaths::ProjectDir());
	UE_LOG(LogTemp, Display, TEXT("| GetProjectFilePath    : %s "), *FPaths::GetProjectFilePath());
	UE_LOG(LogTemp, Display, TEXT("| GetRelativePathToRoot : %s "), *FPaths::GetRelativePathToRoot());
	UE_LOG(LogTemp, Display, TEXT("| GameSourceDir         : %s "), *FPaths::GameSourceDir());
	UE_LOG(LogTemp, Display, TEXT("| LaunchDir             : %s "), *FPaths::LaunchDir());
	*/
	
	//Get Developer setting
	Unreal_Spirits_Settings = GetDefault<UUnreal_Spirits_Settings>();
	if (!Unreal_Spirits_Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("| -------------------------------------------------------------------"));
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Unreal_Spirits_Settings Not Find !"));
		UE_LOG(LogTemp, Error, TEXT("| -------------------------------------------------------------------"));
	}
	
	//Init ServersManager subsystem
	ReloadManager();
}

void URecordingManager::Deinitialize()
{
	Super::Deinitialize();
}

void URecordingManager::ReloadManager()
{
	if (Unreal_Spirits_Settings)
	{
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Init Servers Manager"));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));							
		
		//Init Unreal spirits Setting
		ReloadUnrealSpiritsSettings();
		
		//Check Unreal spirits Folder
		if (!CheckUnrealSpiritsFolder())
		{
			//Create Jar Internal Path !
			CreateUnrealSpiritsFolder();
			
		}


		UE_LOG(LogTemp, Warning, TEXT("| -------------------------  THE END -----------------------------"));
	}
}

//////////////////////////////////
// Unreal Spirits : Folder
//////////////////////////////////

void URecordingManager::ReloadUnrealSpiritsSettings()
{
	if (Unreal_Spirits_Settings)
	{

		//Project Path
		FString Path;

		if (!Unreal_Spirits_Settings->bUseExternalFolder)
		{
			Path = FPaths::LaunchDir();
			FPaths::NormalizeDirectoryName(Path);
			Path += "/" + Unreal_Spirits_Settings->GeneralFolderName;
		}
		else
		{
			Path = Unreal_Spirits_Settings->ExternalFolderPath;
			FPaths::NormalizeDirectoryName(Path);
			Path += "/" + Unreal_Spirits_Settings->GeneralFolderName;
		}

		//Set General folder
		UnrealSpiritsDataFolder = Path;

		UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : UnrealSpirits Folder Name : %s"), *Unreal_Spirits_Settings->GeneralFolderName);
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : UnrealSpirits Folder Path : %s"), *UnrealSpiritsDataFolder);
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------------------------------------"));

	}
}

bool URecordingManager::CheckUnrealSpiritsFolder()
{
	if (FPaths::DirectoryExists(GetUnrealSpiritsFolder()))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Unreal Spirits Folder Find !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Unreal Spirits Folder Not Find !"));
		return false;
	}
}

bool URecordingManager::CreateUnrealSpiritsFolder()
{
	if (IFileManager::Get().MakeDirectory((TCHAR*)*GetUnrealSpiritsFolder()))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Unreal Spirits Folder Created !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Unreal Spirits Folder Not Created !"));
		return false;
	}
}

FString URecordingManager::GetUnrealSpiritsFolder()
{
	return UnrealSpiritsDataFolder;
}

/////////////////////////////////////
// Unreal Spirits : Current Session
/////////////////////////////////////

bool URecordingManager::InitCurrentSession(const FString SessionName)
{
	if (SessionName.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Current Session Name Is Empty !"));
		UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));
		return false;
	}

	CurrentSessionFolder = GetUnrealSpiritsFolder() + "/" + SessionName;
	
	CurrentSessionAudioFolder = GetCurrentSessionFolder() + AUDIO_FOLDER;
	CurrentSessionVideoFolder = GetCurrentSessionFolder() + VIDEO_FOLDER;
	CurrentSessionOtherFolder = GetCurrentSessionFolder() + OTHER_FOLDER;

	UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));
	UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Init Current Session : %s"), *SessionName);
	UE_LOG(LogTemp, Display, TEXT("| "));
	UE_LOG(LogTemp, Display, TEXT("| Current Session Folder         : %s"), *GetCurrentSessionFolder());
	UE_LOG(LogTemp, Display, TEXT("| "));
	UE_LOG(LogTemp, Display, TEXT("| Current Session Audio Folder   : %s"), *GetCurrentSessionAudioFolder());
	UE_LOG(LogTemp, Display, TEXT("| "));
	UE_LOG(LogTemp, Display, TEXT("| Current Session Video Folder   : %s"), *GetCurrentSessionVideoFolder());
	UE_LOG(LogTemp, Display, TEXT("| "));
	UE_LOG(LogTemp, Display, TEXT("| Current Session Other Folder   : %s"), *GetCurrentSessionOtherFolder());
	UE_LOG(LogTemp, Display, TEXT("| "));
	UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));

	if (!CheckCurrentSessionFolders())
	{
		if (CreateCurrentSessionFolders())
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Folders for Current Session Created !"));
			UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Folders for Current Session Not Created !"));
			UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Folders for Current Session already present !"));
		UE_LOG(LogTemp, Warning, TEXT("| ---------------------------------------------------------------------------------------"));
		return true;
	}
}

bool URecordingManager::CheckCurrentSessionFolders()
{
	if (FPaths::DirectoryExists(GetCurrentSessionFolder()))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Unreal Spirits Current Session Folder Find !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Unreal Spirits Current Session Folder Not Find !"));
		return false;
	}
}

bool URecordingManager::CreateCurrentSessionFolders()
{	
	if (IFileManager::Get().MakeDirectory((TCHAR*)*GetCurrentSessionFolder()))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Current Session Folder Created !"));
		//Audio
		if (IFileManager::Get().MakeDirectory((TCHAR*)*GetCurrentSessionAudioFolder()))
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Current Session Audio Folder Created !"));
		}
		//Video
		if (IFileManager::Get().MakeDirectory((TCHAR*)*GetCurrentSessionVideoFolder()))
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Current Session Video Folder Created !"));
		}
		//Other
		if (IFileManager::Get().MakeDirectory((TCHAR*)*GetCurrentSessionOtherFolder()))
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Current Session Other Folder Created !"));
		}
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Unreal Spirits Folder Not Created !"));
		return false;
	}
}

FString URecordingManager::GetCurrentSessionAudioFolder()
{
	return CurrentSessionAudioFolder;
}

FString URecordingManager::GetCurrentSessionFolder()
{
	return CurrentSessionFolder;
}

FString URecordingManager::GetCurrentSessionVideoFolder()
{
	return CurrentSessionVideoFolder;
}

FString URecordingManager::GetCurrentSessionOtherFolder()
{
	return CurrentSessionOtherFolder;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////
// Unreal Spirits : All Sessions
//////////////////////////////////////

void URecordingManager::UpdateAllUnrealSpiritsSessions()
{	
	//Reset List 
	UnrealSpiritsSessionsList.Reset();
	
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	TArray<FString> directoriesToSkip;

	//Craftbukkit
	if (CheckUnrealSpiritsFolder())
	{
		UE_LOG(LogTemp, Warning, TEXT("| -----------------------------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find All Unreal Spirits Sessions..."));
		UE_LOG(LogTemp, Warning, TEXT("| -----------------------------------------------------------------------------"));
		FLocalTimestampDirectoryVisitor UnrealSpiritsVisitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
		PlatformFile.IterateDirectory(*GetUnrealSpiritsFolder(), UnrealSpiritsVisitor);
		for (TMap<FString, FDateTime>::TIterator TimestampIt(UnrealSpiritsVisitor.FileTimes); TimestampIt; ++TimestampIt)
		{
			const FString Sessionfolder = TimestampIt.Key();
			const FString SessionfolderName = FPaths::GetCleanFilename(Sessionfolder);
			UE_LOG(LogTemp, Display, TEXT("| Unreal Spirits Sessions Name   : %s"), *SessionfolderName);
			UnrealSpiritsSessionsList.Add(SessionfolderName);
		}
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| Numbers Of Sessions Find : %s"), *FString::FromInt(UnrealSpiritsSessionsList.Num()));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("| Unreal Spirits Folder Error !"));
		UE_LOG(LogTemp, Warning, TEXT("| -----------------------------------------------------------------------------"));
	}
}

TArray<FString> URecordingManager::GetAllUnrealSpiritsSessionsList()
{
	return UnrealSpiritsSessionsList;
}




















/*
* 
bool URecordingManager::CheckJarInternalPath()
{
	if (FPaths::DirectoryExists(JarInternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Jar Internal Path Find !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Jar Internal Path Not Find !"));
		return false;
	}
}

bool URecordingManager::CreateJarInternalPath()
{
	if (IFileManager::Get().MakeDirectory((TCHAR*)*JarInternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Jar Internal Path Created !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Jar Internal Path Not Created !"));
		return false;
	}
}

bool URecordingManager::CreateJarExternalPath()
{
	if (IFileManager::Get().MakeDirectory((TCHAR*)*JarExternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Jar External Path Created !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Jar External Path Not Created !"));
		return false;
	}
}

FString URecordingManager::GetCurrentJarPath()
{
	if (!bUseJarExternalPath)
	{
		return JarInternalPath;
	}
	else
	{
		return JarExternalPath;
	}
}

FString URecordingManager::GetInternalJarPath()
{
	return JarInternalPath;
}

FString URecordingManager::GetExternalJarPath()
{
	return JarExternalPath;
}

///////////////////////////////////////////
//JAR Minecraft Versions Folders

bool URecordingManager::CheckMinecraftVersionsFolders(bool External)
{
	FString Craftbukkit;
	FString Officiel;
	FString Spigot;

	bool bCraftbukkit = false;
	bool bOfficiel = false;
	bool bSpigot = false;

	if (!External)
	{
		Craftbukkit = JarInternalPath + CRAFTBUKKIT_FOLDER;
		Officiel = JarInternalPath + OFFICIEL_FOLDER;
		Spigot = JarInternalPath + SPIGOT_FOLDER;
	}
	else
	{
		Craftbukkit = JarExternalPath + CRAFTBUKKIT_FOLDER;
		Officiel = JarExternalPath + OFFICIEL_FOLDER;
		Spigot = JarExternalPath + SPIGOT_FOLDER;
	}

	//////////////////////////////////////////////

	if (IFileManager::Get().DirectoryExists((TCHAR*)*Craftbukkit))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Craftbukkit Folder Find !"));
		bCraftbukkit = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Craftbukkit Folder Not Find ! | Create Craftbukkit Folder !"));
		if (IFileManager::Get().MakeDirectory((TCHAR*)*Craftbukkit))
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Craftbukkit Folder Created !"));
			bCraftbukkit = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error Craftbukkit Folder not Created !"));
			return false;
		}
	}

	//////////////////////////////////////////////

	if (FPaths::DirectoryExists(Officiel))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Officiel Folder Find !"));
		bOfficiel = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Officiel Folder Not Find ! | Create Officiel Folder !"));
		if (IFileManager::Get().MakeDirectory((TCHAR*)*Officiel))
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Officiel Folder Created !"));
			bOfficiel = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error Officiel Folder Not Created !"));
			return false;
		}
	}

	//////////////////////////////////////////////

	if (FPaths::DirectoryExists(Spigot))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Spigot Folder Find !"));
		bSpigot = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Spigot Folder Not Find ! | Create Spigot Folder !"));
		if (IFileManager::Get().MakeDirectory((TCHAR*)*Spigot))
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Spigot Folder Created !"));
			bSpigot = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error Spigot Folder Not Created !"));
			return false;
		}
	}

	if (bCraftbukkit && bOfficiel && bSpigot)
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Minecraft Jar version Folders exist !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Minecraft Jar version Folders Not All present !"));
		return false;
	}
}

FString URecordingManager::GetCurrentCraftbukkitJarPath()
{
	FString Path = GetCurrentJarPath() + CRAFTBUKKIT_FOLDER;
	return Path;
}

FString URecordingManager::GetCurrentOfficielJarPath()
{
	FString Path = GetCurrentJarPath() + OFFICIEL_FOLDER;
	return Path;
}

FString URecordingManager::GetCurrentSpigotJarPath()
{
	FString Path = GetCurrentJarPath() + SPIGOT_FOLDER;
	return Path;
}

///////////////////////////////////////////
// Server Manager Path And Folder

void URecordingManager::ReloadServersPathAndFolderConfig()
{
	if (Unreal_Spirits_Settings)
	{
		ServersFolderName = Unreal_Spirits_Settings->ServersFolderName;
		ServersInternalPath = ProjectPath + ServersFolderName;
		bUseServersExternalPath = Unreal_Spirits_Settings->bUseExternalServersPath;
		ServersExternalPath = Unreal_Spirits_Settings->ExternalServersPath + ServersFolderName;

		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers Folder Name   : %s"), *ServersFolderName);
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers Internal Path : %s"), *ServersInternalPath);
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers External Path : %s"), *ServersExternalPath);
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
	}
}

bool URecordingManager::CheckServersInternalPath()
{
	if (FPaths::DirectoryExists(ServersInternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers Internal Path Find !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Servers Internal Path Not Find !"));
		return false;
	}
}

bool URecordingManager::CheckServersExternalPath()
{
	if (FPaths::DirectoryExists(ServersInternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers Internal Path Find !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Servers Internal Path Not Find !"));
		return false;
	}
}

bool URecordingManager::CreateServersInternalPath()
{	
	if (IFileManager::Get().MakeDirectory((TCHAR*)*ServersInternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers Internal Path Created !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Servers Internal Path Not Created !"));
		return false;
	}
}

bool URecordingManager::CreateServersExternalPath()
{
	if (IFileManager::Get().MakeDirectory((TCHAR*)*ServersExternalPath))
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Servers External Path Created !"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Servers External Path Not Created !"));
		return false;
	}
}

FString URecordingManager::GetCurrentServersPath()
{
	if (!bUseServersExternalPath)
	{
		return ServersInternalPath;
	}
	else
	{
		return ServersExternalPath;
	}
}

FString URecordingManager::GetInternalServersPath()
{
	return ServersInternalPath;
}

FString URecordingManager::GetExternalServersPath()
{
	return ServersExternalPath;
}


////////////////////////////////////////////////////////////////////////
// Server Manager : JAR Minecraft Versions 
////////////////////////////////////////////////////////////////////////

void URecordingManager::UpdateJarListsByVersions()
{
	//Reset List 
	CraftbukkitVersions.Reset();
	OfficielVersions.Reset();
	SpigotVersions.Reset();

	//Paths
	FString Craftbukkit;
	FString Officiel;
	FString Spigot;

	if (!bUseJarExternalPath)
	{
		Craftbukkit = JarInternalPath + CRAFTBUKKIT_FOLDER;
		Officiel = JarInternalPath + OFFICIEL_FOLDER;
		Spigot = JarInternalPath + SPIGOT_FOLDER;
	}
	else
	{
		Craftbukkit = JarExternalPath + CRAFTBUKKIT_FOLDER;
		Officiel = JarExternalPath + OFFICIEL_FOLDER;
		Spigot = JarExternalPath + SPIGOT_FOLDER;
	}
	
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	TArray<FString> directoriesToSkip;
	
	//Craftbukkit
	if (FPaths::DirectoryExists(Craftbukkit))
	{
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find Jar Craftbukkit Versions..."));		
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		FLocalTimestampDirectoryVisitor CraftbukkitVisitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
		PlatformFile.IterateDirectory(*Craftbukkit, CraftbukkitVisitor);
		for (TMap<FString, FDateTime>::TIterator TimestampIt(CraftbukkitVisitor.FileTimes); TimestampIt; ++TimestampIt)
		{
			const FString CraftbukkitfilePath = TimestampIt.Key();
			const FString CraftbukkitfileName = FPaths::GetCleanFilename(CraftbukkitfilePath);
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : JAR Craftbukkit Name   : %s"), *CraftbukkitfileName);
			CraftbukkitVersions.Add(CraftbukkitfileName);
		}
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find Jar Craftbukkit : %s"), *FString::FromInt(CraftbukkitVersions.Num()));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Craftbukkit Folder Error !"));
	}

	//Officiel
	if (FPaths::DirectoryExists(Officiel))
	{
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find Jar Officiel Versions..."));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		FLocalTimestampDirectoryVisitor OfficielVisitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
		PlatformFile.IterateDirectory(*Officiel, OfficielVisitor);
		for (TMap<FString, FDateTime>::TIterator TimestampIt(OfficielVisitor.FileTimes); TimestampIt; ++TimestampIt)
		{
			const FString OfficielfilePath = TimestampIt.Key();
			const FString OfficielfileName = FPaths::GetCleanFilename(OfficielfilePath);
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : JAR Officiel Name   : %s"), *OfficielfileName);
			OfficielVersions.Add(OfficielfileName);
		}
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find Jar Officiel : %s"), *FString::FromInt(OfficielVersions.Num()));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Officiel Folder Error !"));
	}
	//Spigot
	if (FPaths::DirectoryExists(Spigot))
	{
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find Jar Spigot Versions..."));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		FLocalTimestampDirectoryVisitor SpigotVisitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
		PlatformFile.IterateDirectory(*Spigot, SpigotVisitor);
		for (TMap<FString, FDateTime>::TIterator TimestampIt(SpigotVisitor.FileTimes); TimestampIt; ++TimestampIt)
		{
			const FString SpigotfilePath = TimestampIt.Key();
			const FString SpigotfileName = FPaths::GetCleanFilename(SpigotfilePath);
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : JAR Spigot Name   : %s"), *SpigotfileName);
			SpigotVersions.Add(SpigotfileName);
		}
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Find Jar Spigot : %s"), *FString::FromInt(SpigotVersions.Num()));
		UE_LOG(LogTemp, Warning, TEXT("| ----------------------------------------------------------"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Spigot Folder Error !"));
	}
}

TArray<FString> URecordingManager::GetCraftbukkitVersionsList()
{
	return CraftbukkitVersions;
}

TArray<FString> URecordingManager::GetOfficielVersionsList()
{
	return OfficielVersions;
}

TArray<FString> URecordingManager::GetSpigotVersionsList()
{
	return SpigotVersions;
}

bool URecordingManager::IsJarVersionPresent(const EMC_ServerType ServerType, const FString JarVersion)
{
	TArray<FString> List;
	switch (ServerType)
	{
	case EMC_ServerType::JAVE_EDITION_NULL:
		return false;
		break;
	case EMC_ServerType::CRAFTBUKKIT:
		List = CraftbukkitVersions;
		break;
	case EMC_ServerType::OFFFICIEL:
		List = OfficielVersions;
		break;
	case EMC_ServerType::SPIGOT:
		List = SpigotVersions;
		break;
	}

	for (size_t i = 0; i < List.Num(); i++)
	{
		if (JarVersion == List[i])
		{
			return true;			
		}
	}
	return false;
}

bool URecordingManager::CopyJarVersionInServerFolder(const EMC_ServerType ServerType,const FString JarVersion, const FString ServerName)
{	
	//Create JAR File Path
	FString JarFolderPath;

	//Switch Server Type
	switch (ServerType)
	{
	case EMC_ServerType::JAVE_EDITION_NULL:
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : CopyJarVersionInServerFolder() Server Type Null !"));
		UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));
		return false;
		break;
	case EMC_ServerType::CRAFTBUKKIT:
		JarFolderPath = GetCurrentCraftbukkitJarPath();
		break;
	case EMC_ServerType::OFFFICIEL:
		JarFolderPath = GetCurrentOfficielJarPath();
		break;
	case EMC_ServerType::SPIGOT:
		JarFolderPath = GetCurrentSpigotJarPath();
		break;
	}

	//Set File Path with Jar File Name
	JarFolderPath += "/" + JarVersion;

	////////////////////////////////////////////////////

	//Create Servers Folder Path
	FString ServersFolderPath = GetCurrentServersPath() + "/" + ServerName;
	
	//Set Servers Folder Path with Jar File Name
	ServersFolderPath += "/" + JarVersion;
	
	////////////////////////////////////////////////////

	UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));
	UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Copy JAR File ! "));
	UE_LOG(LogTemp, Display, TEXT("| JAR File Path      : %s"), *JarFolderPath);
	UE_LOG(LogTemp, Display, TEXT("| Server Folder Path : %s"), *ServersFolderPath);
	UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));


	//Check JAR File exist
	if (!IFileManager::Get().FileExists((TCHAR*)*JarFolderPath))
	{
		UE_LOG(LogTemp, Error, TEXT("| URecordingManager : JAR Version File does not exist !"));		
		UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : JAR Version File Find !"));
		//Check Server Folder exist
		if (!FPaths::DirectoryExists(ServersFolderPath))
		{			
			UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Server Folder Not Find !"));
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Server Folder Find !"));

			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
			if (!PlatformFile.CopyFile((TCHAR*)*ServersFolderPath, (TCHAR*)*JarFolderPath))
			{
				UE_LOG(LogTemp, Error, TEXT("| URecordingManager : JAR Version File copy Error !"));
				return false;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : JAR Version File Was Copied !"));
				return true;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Server Manager Functiuns
////////////////////////////////////////////////////////////////////////

bool URecordingManager::CreateNewMinecraftServer(FMC_ServerInfo Infos, FMC_ServerBat BatInfos)
{
	UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
	UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Create NewMinecraft Server   : %s"), *Infos.ServerName);
	UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));

	//Set Server Foler
	FString ServerFolder = GetCurrentServersPath() + "/" + Infos.ServerName;	
	UE_LOG(LogTemp, Display, TEXT("| Server Folder Path : %s "), *ServerFolder);


	//Folder Exist
	if (FPaths::DirectoryExists(ServerFolder))
	{
		UE_LOG(LogTemp, Error, TEXT("| Server Folder Exist !"));
		UE_LOG(LogTemp, Error, TEXT("| For not delete another server data !"));
		UE_LOG(LogTemp, Error, TEXT("| The creation of the new server has been interrupted !"));
		UE_LOG(LogTemp, Warning, TEXT("| -----------------------------------------------------------------------"));
		return false;
	}
	else
	{
		//Create Server Folder
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Creating the server folder !"));
		if (IFileManager::Get().MakeDirectory((TCHAR*)*ServerFolder))
		{
			UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : The server folder has been created !"));
			UE_LOG(LogTemp, Display, TEXT("| --------------------------------------------------------"));

			//Set Jar Version
			FString JarVersion;
			switch (Infos.ServerType)
			{
			case EMC_ServerType::JAVE_EDITION_NULL:
				UE_LOG(LogTemp, Error, TEXT("| The server can't created Server Type is null in ServerInfo !"));
				UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));
				return false;
				break;
			case EMC_ServerType::CRAFTBUKKIT:
				JarVersion = UMC_Outils_Structures::EMC_CraftbukkitVersionToString(Infos.CraftbukkitVersion);
				break;
			case EMC_ServerType::OFFFICIEL:
				JarVersion = UMC_Outils_Structures::EMC_OfficielVersionToString(Infos.OfficielVersion);
				break;
			case EMC_ServerType::SPIGOT:
				JarVersion = UMC_Outils_Structures::EMC_SpigotVersionToString(Infos.SpigotVersion);
				break;
			}
			JarVersion += ".jar";

			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Jar version : %s "), *JarVersion);

			if (!IsJarVersionPresent(Infos.ServerType, JarVersion))
			{
				UE_LOG(LogTemp, Error, TEXT("| URecordingManager : JAR version is not present in Java Folder !"));
				UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
				return false;
			}
			else
			{		
				UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : JAR version is present in Java Folder !"));
				//Copy Jar File
				if (!CopyJarVersionInServerFolder(Infos.ServerType, JarVersion, Infos.ServerName))
				{
					UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error while Copy Jar Version File In Server Folder !"));
					UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
					return false;
				}
				else
				{					
					//Create FirstStartServer.bat				
					if (!BatManager->CreateFirstStartServerBat(JarVersion, ServerFolder))
					{
						UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error while creating StartServer.bat !"));
						UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
						return false;
					}
					else
					{
						//Create StartServer.bat				
						if (!BatManager->CreateStartServerBat(JarVersion, ServerFolder, BatInfos.ServerMemory, BatInfos.Params))
						{
							UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error while creating StartServer.bat !"));
							UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
							return false;
						}
						else
						{							
							//Create BackupServer.bat												
							if (!BatManager->CreateBackupServerBat(ServerFolder))
							{
								UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error while creating BackupServer.bat !"));
								UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
								return false;
							}
							else
							{
								UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
								UE_LOG(LogTemp, Warning, TEXT("| Server was save in Servers Manager !"));
								UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
								
								//Create New Server
								FMC_Server NewServer;
								NewServer.info = Infos;								
								NewServer.bat = BatInfos;

								//Save The server in Servers Manager
								Servers.Add(NewServer);
								//Save The server in Save Manager					
								if (MC_SaveManager->SaveNewServer(NewServer))
								{
									UE_LOG(LogTemp, Warning, TEXT("| Server Saved in Save Manager !"));
								}
								else
								{
									UE_LOG(LogTemp, Error, TEXT("| Server Not Saved in Save Manager !"));
								}
								
								UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
								
								//First Start of Server
								if (!BatManager->FirstStartServer(ServerFolder))
								{
									UE_LOG(LogTemp, Display, TEXT("|  Server : %s  | First Start Not Effectued !"), *Infos.ServerName);
									return false;
								}
								else
								{
									//Eula Validation 
									if (!StartEulaValidation(Infos.ServerName))
									{
										UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Server : %s  | Eula Not Valided !"), *Infos.ServerName);
										UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));
										return false;
									}
									else
									{
										//New PrcessId
										int32 ProcessId = -1;

										//Check response
										if (!BatManager->StartServer(ServerFolder, ProcessId))
										{
											UE_LOG(LogTemp, Display, TEXT("| Server : %s  | Not Started !"), *Infos.ServerName);
											UE_LOG(LogTemp, Warning, TEXT("| ------------------------------------------------------------------------------"));
											return false;
										}
										else
										{
											//Add ProcessId To List
											ServersProcessId.Add(ProcessId);

											//Debub The End
											UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
											UE_LOG(LogTemp, Display, TEXT("| "));
											UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Start Of Server  !"));
											UE_LOG(LogTemp, Display, TEXT("| "));
											UE_LOG(LogTemp, Display, TEXT("| Server Name : %s !"), *Infos.ServerName);
											UE_LOG(LogTemp, Display, TEXT("| "));
											UE_LOG(LogTemp, Display, TEXT("| PorcessId   : %s !"), *FString::FromInt(ProcessId));
											UE_LOG(LogTemp, Display, TEXT("| "));
											UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
											return true;
										}
									}
								}
							}
						}						
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Error while creating server folder !"));
			UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------------------------------------------------------------"));
			return false;
		}
	}
}

bool URecordingManager::StartEulaValidation(const FString ServerName)
{		
	UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------"));
	UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Start Eula Validation : %s !"), *ServerName);
	UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------"));
	
	//Set Server Foler
	FString ServerFolder = GetCurrentServersPath() + "/" + ServerName;
	UE_LOG(LogTemp, Display, TEXT("| Server Folder Path : %s "), *ServerFolder);

	if (!FPaths::DirectoryExists(ServerFolder))
	{
		UE_LOG(LogTemp, Error, TEXT("| Server Folder Not Find !"));		
		UE_LOG(LogTemp, Warning, TEXT("| --------------------------------------------------"));
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Server Folder Find  !"));

		//Create Eula File 
		FString Filename = GetCurrentServersPath() + "/" + ServerName + EULA_FILE;
		UE_LOG(LogTemp, Display, TEXT("| URecordingManager :  Eula Filename : %s"), *Filename);

		//Check Eula file
		if (!IFileManager::Get().FileExists((TCHAR*)*Filename))
		{
			UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Eula File does not exist !"));
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Eula File Find !"));
			//Load Eula
			TArray<FString> Ligns;
			if (!FFileHelper::LoadFileToStringArray(Ligns, (TCHAR*)*Filename))
			{
				UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Eula File Not Loaded !"));
				return false;
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Eula File Loaded !"));
			}
			bool FindEulaLign = false;
			//Search Eula Lign
			for (size_t i = 0; i < Ligns.Num(); i++)
			{
				if (Ligns[i].Contains("Eula=false"))
				{
					Ligns[i] = "eula=true";
					FindEulaLign = true;
					break;
				}
			}
			if (!FindEulaLign)
			{
				UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Eula Lign Not Find !"));
				return false;
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("| URecordingManager : Eula Lign Find !"));
				//Save Eula File 
				if (!FFileHelper::SaveStringArrayToFile(Ligns, (TCHAR*)*Filename))
				{
					UE_LOG(LogTemp, Error, TEXT("| URecordingManager : Eula File Not Saved !"));
					return false;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("| URecordingManager : Eula File Saved !"));
					return true;
				}
			}
		}
	}
}

TArray<FMC_Server> URecordingManager::GetAllServers()
{
	return Servers;
}

*/