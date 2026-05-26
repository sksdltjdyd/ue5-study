// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWebSocketActor.h"
#include "WebSocketsModule.h" // 웹소켓 모듈 사용을 위해 필수 포함
#include "TimerManager.h" // 타이머 사용을 위해 필수 포함

// Sets default values
AMyWebSocketActor::AMyWebSocketActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CurrentRetryCount = 0; // 재시도 횟수 초기화

}

// Called when the game starts or when spawned
void AMyWebSocketActor::BeginPlay()
{
	Super::BeginPlay();
    InitializeWebSocket(); // 여기서 호출

}

void AMyWebSocketActor::InitializeWebSocket()
{
   // 1. 웹소켓 모듈이 로드되어 있는지 확인하고 강제 로드
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	// 2. 서버 주소 설정 (로컬 테스트용 예시 : ws://127.0.0.1:8080)
	FString ServerURL = TEXT("ws://127.0.0.1:8080");
	FString ServerProtocol = TEXT("ws");

	// 3. 웹소켓 객체 생성하여 스마트 포인터에 할당
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

	// 연결 성공 시 실행될 로직 등록
    WebSocket->OnConnected().AddLambda([this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("서버에 성공적으로 연결되었습니다!"));
        
        CurrentRetryCount = 0; // 연결 성공 시 재시도 횟수 초기화

        // 연결이 확실히 완료된 이 시점에서 첫 메시지를 보내는 것이 가장 안전합니다.
        WebSocket->Send(TEXT("Hello Server, I am Unreal Engine!"));
    });

    // 연결 실패 시 실행될 로직 등록
    WebSocket->OnConnectionError().AddLambda([this](const FString& Error)
    {
        UE_LOG(LogTemp, Error, TEXT("연결 에러 발생: %s"), *Error);
        // 연결 자체가 실패했을 때도 재연결을 시도합니다.
        TriggerReconnection();
    });

    // [오늘 추가] 서버로부터 메시지 수신 이벤트
    WebSocket->OnMessage().AddLambda([](const FString& MessageString)
    {
        // 서버가 보낸 텍스트를 로그에 출력합니다. (내일은 여기서 JSON을 파싱합니다)
        UE_LOG(LogTemp, Log, TEXT("서버로부터 메시지 수신: %s"), *MessageString);
    });

    // [오늘 추가] 연결 종료 이벤트
    WebSocket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
    {
        UE_LOG(LogTemp, Warning, TEXT("서버와 연결이 끊어졌습니다. 코드: %d, 이유: %s"), StatusCode, *Reason);
        
        // 정상적으로 우리가 Close()를 호출한 게 아니라면 재연결 시도
        if (!bWasClean)
        {
            TriggerReconnection();
        }
    });

	// 4. 실제 서버로 접속 시도 시작 (비동기로 진행됨)
    WebSocket->Connect();
}

// [오늘 추가] 타이머를 이용한 안전한 재연결 로직
void AMyWebSocketActor::TriggerReconnection()
{
    // 이미 재연결 타이머가 돌고 있다면 중복 등록 방지
    if (GetWorldTimerManager().IsTimerActive(ReconnectTimerHandle)) return;

    if (CurrentRetryCount < MaxRetryAttempts)
    {
        CurrentRetryCount++;
        UE_LOG(LogTemp, Warning, TEXT("보안: %.1f초 후 재연결을 시도합니다... (시도 횟수: %d/%d)"), RetryDelay, CurrentRetryCount, MaxRetryAttempts);

        // 중요: 3초(RetryDelay) 후에 InitializeWebSocket 함수를 비동기로 호출하라고 타이머에 등록
        GetWorldTimerManager().SetTimer(ReconnectTimerHandle, this, &AMyWebSocketActor::InitializeWebSocket, RetryDelay, false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("최대 재연결 시도 횟수를 초과했습니다. 서버 상태를 확인하세요."));
    }
}

// Called every frame
void AMyWebSocketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyWebSocketActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

    // 게임이 끝나면 타이머도 깔끔하게 취소해 줍니다.
    GetWorldTimerManager().ClearTimer(ReconnectTimerHandle);

    // 웹소켓이 유효하고, 아직 통신 파이프가 열려있다면 닫기
    if (WebSocket.IsValid() && WebSocket->IsConnected())
    {
        WebSocket->Close();
    }

    Super::EndPlay(EndPlayReason);
}