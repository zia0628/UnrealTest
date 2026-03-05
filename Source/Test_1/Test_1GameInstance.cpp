// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_1GameInstance.h"

// Test_1GameInstance.cpp
#include "Test_1GameInstance.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"

UTest_1GameInstance::UTest_1GameInstance()
{
	// 델리게이트와 함수 연결
	CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UTest_1GameInstance::OnCreateSessionComplete);
	FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UTest_1GameInstance::OnFindSessionsComplete);
	JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UTest_1GameInstance::OnJoinSessionComplete);
}

// --- [방 만들기] ---
void UTest_1GameInstance::HostGame()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsLANMatch = true;          // 테스트를 위해 LAN 모드
			SessionSettings.NumPublicConnections = 2;   // 2인 협동
			SessionSettings.bShouldAdvertise = true;    // 검색 노출
			SessionSettings.bUsesPresence = true;       // 상태 정보 사용
			SessionSettings.bAllowJoinInProgress = true;

			// 델리게이트 등록 후 세션 생성
			SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
			SessionInterface->CreateSession(0, FName("Test1_Session"), SessionSettings);
		}
	}
}

void UTest_1GameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// 방장이 서버 맵으로 이동 (?listen 옵션이 리슨 서버를 켭니다)
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
		}
	}
}

// --- [방 찾기 및 참가] ---
void UTest_1GameInstance::JoinGame()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->bIsLanQuery = true;
			SessionSearch->MaxSearchResults = 10;
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

			SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}

void UTest_1GameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful && SessionSearch.IsValid() && SessionSearch->SearchResults.Num() > 0)
	{
		// 첫 번째로 찾은 방에 접속 시도
		SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
		SessionInterface->JoinSession(0, FName("Test1_Session"), SessionSearch->SearchResults[0]);
	}
}

void UTest_1GameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		// 클라이언트가 서버의 IP 주소를 얻어 이동
		APlayerController* PC = GetFirstLocalPlayerController();
		if (PC)
		{
			FString ConnectionInfo = "";
			SessionInterface->GetResolvedConnectString(SessionName, ConnectionInfo);
			if (!ConnectionInfo.IsEmpty())
			{
				PC->ClientTravel(ConnectionInfo, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}