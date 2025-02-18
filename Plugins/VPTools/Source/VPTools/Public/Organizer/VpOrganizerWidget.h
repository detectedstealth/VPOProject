// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "VpOrganizerWidget.generated.h"

USTRUCT(BlueprintType)
struct FVpFolder
{
	GENERATED_BODY()

	FVpFolder();
	explicit FVpFolder(FString InFolderName, bool InShouldGenerateFolder = true);
	bool GenerateFolder(FString ParentPath) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folder", DisplayName = "Name")
	FString FolderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Folder", DisplayName = "Generate Folder?")
	bool ShouldGenerateFolder = true;
};

USTRUCT(BlueprintType)
struct FMainVpFolder
{
	GENERATED_BODY()

	explicit FMainVpFolder(const FString& InFolderName = TEXT(""));
	bool GenerateFolders(FString ParentPath) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainVpFolder")
	FVpFolder MainFolder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubFolders")
	TArray<FVpFolder> SubFolders;
	
};


USTRUCT(BlueprintType)
struct FTopLevelFolders
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Main Folders")
	TArray<FMainVpFolder> MainFolders;

	// Properties ordered how UE will organize them by default.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Animation")
	FMainVpFolder AnimationFolder = FMainVpFolder(TEXT("Animation"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Assets")
	FMainVpFolder AssetsFolder = FMainVpFolder(TEXT("Assets"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Blueprints")
	FMainVpFolder BlueprintsFolder = FMainVpFolder(TEXT("Blueprints"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Development")
	FMainVpFolder DevelopmentFolder = FMainVpFolder(TEXT("DEV"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Materials")
	FMainVpFolder MaterialsFolder = FMainVpFolder(TEXT("Materials"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Megascans")
	FMainVpFolder MegascansFolder = FMainVpFolder(TEXT("Megascans"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Metahumans")
	FMainVpFolder MetahumansFolder = FMainVpFolder(TEXT("Metahumans"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Movies")
	FMainVpFolder MoviesFolder = FMainVpFolder(TEXT("Movies"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="MSPresets")
	FMainVpFolder MSPresetsFolder = FMainVpFolder(TEXT("MSPresets"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="SEQs")
	FMainVpFolder SequencesFolder = FMainVpFolder(TEXT("SEQs"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="SETs")
	FMainVpFolder SetsFolder = FMainVpFolder(TEXT("SETs"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Sounds")
	FMainVpFolder SoundsFolder = FMainVpFolder(TEXT("Sounds"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="Textures")
	FMainVpFolder TexturesFolder = FMainVpFolder(TEXT("Textures"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="UI")
	FMainVpFolder UIFolder = FMainVpFolder(TEXT("UI"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopLevelFolders", DisplayName="VFX")
	FMainVpFolder VFXFolder = FMainVpFolder(TEXT("VFX"));
};

USTRUCT(BlueprintType)
struct FVpFileStructure
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Top Level File Structure")
	FString RootFolderName = TEXT("Content");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Top Level File Structure")
	FTopLevelFolders TopLevelFolders;
};

/**
 * 
 */
UCLASS()
class VPTOOLS_API UVpOrganizerWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UVpOrganizerWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrganizerFolderStructure")
	FVpFileStructure FileStructure;

	UFUNCTION(BlueprintCallable, Category = "OrganizerFolderStructure")
	void UpdateFileStructure();

	void SaveFileStructure();
	void LoadFileStructure();

private:
	FString PersistantFilePath = TEXT("/Game/Plugins/VPTools/Organizer/VpOrganizerWidget.json");
};
