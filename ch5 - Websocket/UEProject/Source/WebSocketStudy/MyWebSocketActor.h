// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IWebSocket.h" // 웹소켓 인터페이스 필수 포함
#include "MyWebSocketActor.generated.h"

UCLASS()
class WEBSOCKETSTUDY_API AMyWebSocketActor : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// SendJsonData 함수를 선언
	void SendJsonData();

private:
	// 웹소켓 객체
	// 객체를 안전하게 보관할 스마트 포인터
	TSharedPtr<IWebSocket> WebSocket;

	// [오늘 추가] 웹소켓 초기화 및 연결을 담당하는 함수
    void InitializeWebSocket();

    // [오늘 추가] 재연결을 안전하게 시도할 함수
    void TriggerReconnection();

    // [오늘 추가] 재연결을 제어하기 위한 변수들
    FTimerHandle ReconnectTimerHandle; // 타이머 관리자
    int32 CurrentRetryCount;           // 현재 재시도 횟수
    const int32 MaxRetryAttempts = 5;  // 최대 재시도 횟수
    const float RetryDelay = 3.0f;     // 재시도 간격 (3초)

protected:
	// Sets default values for this actor's properties
	AMyWebSocketActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
