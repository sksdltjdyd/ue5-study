// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWebSocketActor.h"
#include "WebSocketsModule.h" // 웹소켓 모듈 사용을 위해 필수 포함

// Sets default values
AMyWebSocketActor::AMyWebSocketActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyWebSocketActor::BeginPlay()
{
	Super::BeginPlay();

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
        
        // 연결이 확실히 완료된 이 시점에서 첫 메시지를 보내는 것이 가장 안전합니다.
        WebSocket->Send(TEXT("Hello Server, I am Unreal Engine!"));
    });

    // 연결 실패 시 실행될 로직 등록
    WebSocket->OnConnectionError().AddLambda([](const FString& Error)
    {
        UE_LOG(LogTemp, Error, TEXT("연결 에러 발생: %s"), *Error);
    });

	// 4. 실제 서버로 접속 시도 시작 (비동기로 진행됨)
    WebSocket->Connect();

}

// Called every frame
void AMyWebSocketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyWebSocketActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 웹소켓이 유효하고, 아직 통신 파이프가 열려있다면 닫기
    if (WebSocket.IsValid() && WebSocket->IsConnected())
    {
        WebSocket->Close();
    }

    Super::EndPlay(EndPlayReason);
}