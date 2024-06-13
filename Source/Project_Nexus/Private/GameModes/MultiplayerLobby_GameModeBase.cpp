// Copyright 2018-2024 In Series Studio GmbH


#include "GameModes/MultiplayerLobby_GameModeBase.h"

	AMultiplayerLobby_GameModeBase::AMultiplayerLobby_GameModeBase(){
        // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	    PrimaryActorTick.bCanEverTick = true;
        
        IsJoinable = false;
    }

	void AMultiplayerLobby_GameModeBase::HostLANGame(){
        //?Listen make it launch to a listen server
        UWorld* World = GetWorld();
        if(World){
            World->ServerTravel("/Game/Levels/Online/MultiplayerLobbyLevel?Listen");
        }
    }

	void AMultiplayerLobby_GameModeBase::JoinLANGame(const FString& Adress){
        APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
        if(PC){
            PC->ClientTravel(Adress, TRAVEL_Absolute);
        }
    }