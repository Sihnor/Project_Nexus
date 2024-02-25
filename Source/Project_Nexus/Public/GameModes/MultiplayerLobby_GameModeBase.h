// Copyright 2018-2024 In Series Studio GmbH

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerLobby_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API AMultiplayerLobby_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
	AMultiplayerLobby_GameModeBase();

	UFUNCTION(BlueprintCallable)
	void HostLANGame();

	UFUNCTION(BlueprintCallable)
	void JoinLANGame(const FString& Adress);

	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerState", meta = (AllowPrivateAccess = "true"))
		bool IsJoinable;
};
