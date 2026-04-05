// Scientific Ways

#pragma once

#include "Engine/DataAsset.h"

#include "ScWExperienceDescription.generated.h"

class FString;
class UCommonSession_HostSessionRequest;
class UObject;
class UTexture2D;
class UUserWidget;
struct FFrame;

/**
 *	Description of settings used to display experiences in the UI and start a new session.
 */
UCLASS(BlueprintType)
class UScWExperienceDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** The specific map to load */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapID;

	/** The gameplay experience to load */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere, meta = (AllowedTypes = "ScWExperience"))
	FPrimaryAssetId ExperienceID;

	/** Extra arguments passed as URL options to the game */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	TMap<FString, FString> ExtraArgs;

	/** Primary title in the UI */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	FText TileTitle;

	/** Secondary title */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	FText TileSubTitle;

	/** Full description */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	FText TileDescription;

	/** Icon used in the UI */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> TileIcon;

	/** The loading screen widget to show when loading into (or back out of) a given experience */
	UPROPERTY(Category = "LoadingScreen", BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<UUserWidget> LoadingScreenWidget;

	/** If true, this is a default experience that should be used for quick play and given priority in the UI */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	bool bIsDefaultExperience = false;

	/** If true, this will show up in the experiences list in the front-end */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	bool bShowInFrontEnd = true;

	/** If true, a replay will be recorded of the game */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	bool bRecordReplay = false;

	/** Max number of players for this session */
	UPROPERTY(Category = "Experience", BlueprintReadWrite, EditAnywhere)
	int32 MaxPlayerCount = 16;

public:
	/** Create a request object that is used to actually start a session with these settings */
	//UFUNCTION(BlueprintCallable, BlueprintPure=false, meta = (WorldContext = "WorldContextObject"))
	//UCommonSession_HostSessionRequest* CreateHostingRequest(const UObject* WorldContextObject) const;
};
