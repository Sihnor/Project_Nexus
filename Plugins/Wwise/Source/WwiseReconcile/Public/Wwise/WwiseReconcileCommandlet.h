/*******************************************************************************
The content of this file includes portions of the proprietary AUDIOKINETIC Wwise
Technology released in source code form as part of the game integration package.
The content of this file may not be used without valid licenses to the
AUDIOKINETIC Wwise Technology.
Note that the use of the game engine is subject to the Unreal(R) Engine End User
License Agreement at https://www.unrealengine.com/en-US/eula/unreal
 
License Usage
 
Licensees holding valid licenses to the AUDIOKINETIC Wwise Technology may use
this file in accordance with the end user license agreement provided with the
software or, alternatively, in accordance with the terms contained
in a written agreement between you and Audiokinetic Inc.
Copyright (c) 2023 Audiokinetic Inc.
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "AkAudioEvent.h"
#include "WwiseReconcile.h"
#include "Commandlets/Commandlet.h"
#include "Wwise/Metadata/WwiseMetadataBasicReference.h"

#include "WwiseReconcileCommandlet.generated.h"

class UAkAssetFactory;
class FWwiseProjectDatabase;
class FAssetRegistryModule;
class FAssetToolsModule;

UCLASS()
class WWISERECONCILE_API UWwiseReconcileCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	virtual int32 Main(const FString& Params) override;
	UWwiseReconcileCommandlet();

private:
	/** All commandline Tokens */
	TArray<FString> CmdTokens;

	/** All commandline switches */
	TArray<FString> CmdSwitches;

	// Array of all existing UAkAudioType uassets
	TArray<FAssetData> Assets;

	// Array of uassets and their counterpart in the SoundBanks
	TArray<FWwiseReconcileItem> ReconcileItems;

	/** Prints command line arguments */
	void PrintHelp();
};
