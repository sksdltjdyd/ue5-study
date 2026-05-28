// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IWebSocket.h"
#include "Http.h" // 지난주에 배운 HTTP 모듈 포함
#include "MyComboActor.generated.h"

UCLASS()
class WEBSOCKETSTUDY_API AMyComboActor : public AActor
{
    GENERATED_BODY()

public:    
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    // --- HTTP 관련 함수 ---
    void RequestInitialData();
    void OnInitialDataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    // --- WebSocket 관련 함수 (어제와 동일) ---
    TSharedPtr<IWebSocket> WebSocket;
    void InitializeWebSocket();
};
