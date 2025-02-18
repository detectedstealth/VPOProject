// Copyright Bruce Wade, 2024

#include "Organizer/VpOrganizerWidget.h"
#include "EditorAssetLibrary.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

FVpFolder::FVpFolder()
{
	FVpFolder(TEXT(""));
}

FVpFolder::FVpFolder(FString InFolderName, bool InShouldGenerateFolder)
{
	FolderName = InFolderName;
	ShouldGenerateFolder = InShouldGenerateFolder;
}

bool FVpFolder::GenerateFolder(FString ParentPath) const
{
	if (!ShouldGenerateFolder || FolderName.IsEmpty()) return false;
	
	// If the folder already exists skip creating it. This can happen if generation button is clicked multiple times.
	if (UEditorAssetLibrary::DoesAssetExist(FPaths::Combine(ParentPath, FolderName))) return true;
	
	UEditorAssetLibrary::MakeDirectory(FPaths::Combine(ParentPath, FolderName));
	return true;
}

FMainVpFolder::FMainVpFolder(const FString& InFolderName)
{
	MainFolder = FVpFolder(InFolderName);
}

bool FMainVpFolder::GenerateFolders(FString ParentPath) const
{
	if (!MainFolder.GenerateFolder(ParentPath)) return false;
	for (const FVpFolder& Folder : SubFolders)
	{
		if (Folder.ShouldGenerateFolder)
		{
			Folder.GenerateFolder(FPaths::Combine(ParentPath, MainFolder.FolderName));
		}
	}
	return true;
}


UVpOrganizerWidget::UVpOrganizerWidget()
{
	LoadFileStructure();
}

void UVpOrganizerWidget::UpdateFileStructure()
{
	FString RootFolder = FPaths::Combine(TEXT("/"), TEXT("Game"));
	if (!FileStructure.RootFolderName.StartsWith(TEXT("Content")))
	{
		RootFolder = FPaths::Combine(TEXT("/Game"), FileStructure.RootFolderName);
		UEditorAssetLibrary::MakeDirectory(RootFolder);
	}

	//  Assets
	if (FileStructure.TopLevelFolders.AssetsFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Blueprints
	if (FileStructure.TopLevelFolders.BlueprintsFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Animations
	if (FileStructure.TopLevelFolders.AnimationFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Sequences
	if (FileStructure.TopLevelFolders.SequencesFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Development
	if (FileStructure.TopLevelFolders.DevelopmentFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Sets
	if (FileStructure.TopLevelFolders.SetsFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  VFX
	if (FileStructure.TopLevelFolders.VFXFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Materials
	if (FileStructure.TopLevelFolders.MaterialsFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Textures
	if (FileStructure.TopLevelFolders.TexturesFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Movies
	if (FileStructure.TopLevelFolders.MoviesFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Sounds
	if (FileStructure.TopLevelFolders.SoundsFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Metahumans
	if (FileStructure.TopLevelFolders.MetahumansFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  Megascans
	if (FileStructure.TopLevelFolders.MegascansFolder.GenerateFolders(RootFolder))
	{
		
	}

	// MSPresets
	if (FileStructure.TopLevelFolders.MSPresetsFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	//  UI
	if (FileStructure.TopLevelFolders.UIFolder.GenerateFolders(RootFolder))
	{
		
	}
	
	SaveFileStructure();
}

void UVpOrganizerWidget::SaveFileStructure()
{
	TSharedPtr<FJsonObject> JsonData = FJsonObjectConverter::UStructToJsonObject(FileStructure);
	if (!JsonData.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("JsonData for Tool is invalid"));
		return;
	}

	FString JsonString;
	if (!FJsonSerializer::Serialize(JsonData.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to serialize JsonData for Tool"));
		return;
	}
	
	FString FilePath = FPaths::Combine(FPaths::ProjectPluginsDir() + TEXT("VPTools/VpOrganizerWidget.json"));
	FFileHelper::SaveStringToFile(JsonString, *FilePath);
	UE_LOG(LogTemp, Warning, TEXT("File saved to %s"), *FilePath)
}

void UVpOrganizerWidget::LoadFileStructure()
{
	FString FilePath = FPaths::Combine(FPaths::ProjectPluginsDir() + TEXT("VPTools/VpOrganizerWidget.json"));
	FString JsonString;
	
	FFileHelper::LoadFileToString(JsonString, *FilePath);
	if (JsonString.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Issue reading file"));
		return;
	}
	TSharedPtr<FJsonObject> JsonData;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), JsonData))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to deserialize JsonData for Tool"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("File loaded from %s"), *FilePath)

	if (!JsonData.IsValid())
	{
		FileStructure = FVpFileStructure();
		return;
	}

	if (!FJsonObjectConverter::JsonObjectToUStruct<FVpFileStructure>(JsonData.ToSharedRef(), &FileStructure))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to convert JsonData for Tool into FileStructure"));
		FileStructure = FVpFileStructure();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("FileStructure loaded from %s"), *FilePath)
	
}
