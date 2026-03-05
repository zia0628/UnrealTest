// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Test_1GameInstance.generated.h"
// Test_1GameInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h" // 세션 인터페이스 필수
#include "Test_1GameInstance.generated.h"

UCLASS()
class TEST_1_API UTest_1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTest_1GameInstance();

	// 1. 외부(UI 버튼 등)에서 호출할 함수
	UFUNCTION(BlueprintCallable)
	void HostGame(); // 방 만들기

	UFUNCTION(BlueprintCallable)
	void JoinGame(); // 방 찾아서 들어가기

protected:
	// 2. 세션 이벤트 처리를 위한 콜백 함수들
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// 3. 세션 인터페이스 포인터와 검색 결과 저장용
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// 델리게이트 핸들 (등록 및 해제용)
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
};
/**
 * 
 */
