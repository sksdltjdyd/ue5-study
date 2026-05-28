// Fill out your copyright notice in the Description page of Project Settings.


#include "MyComboActor.h"
#include "WebSocketsModule.h"

void AMyComboActor::BeginPlay()
{
    Super::BeginPlay();
    
    // 1. 웹소켓이 아니라 HTTP 요청부터 먼저 시작합니다!
    RequestInitialData(); 
}

// 2. HTTP GET 요청 (초기 상태 다운로드)
void AMyComboActor::RequestInitialData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    
    // 응답이 오면 OnInitialDataReceived 함수를 실행하라고 바인딩
    Request->OnProcessRequestComplete().BindUObject(this, &AMyComboActor::OnInitialDataReceived);
    
    // 임시 초기 데이터 API 주소 (실제 서버 주소로 변경 필요)
    Request->SetURL(TEXT("http://127.0.0.1:8080/api/init_state"));
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();
    
    UE_LOG(LogTemp, Warning, TEXT("HTTP 초기 데이터 요청을 보냈습니다."));
}

// 3. HTTP 응답 수신
void AMyComboActor::OnInitialDataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("HTTP 초기 데이터 수신 성공: %s"), *Response->GetContentAsString());
        
        // TODO: 여기서 수신된 JSON을 파싱하여 초기 액터들을 배치합니다.
        
        // 4. 초기 세팅이 무사히 끝났으니, 이제 실시간 조작을 위해 웹소켓을 연결합니다!
        InitializeWebSocket(); 
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP 초기 데이터 수신 실패! 웹소켓을 연결하지 않습니다."));
    }
}

// 5. 웹소켓 연결 (이전 코드와 동일하므로 뼈대만 작성)
void AMyComboActor::InitializeWebSocket()
{
    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    WebSocket = FWebSocketsModule::Get().CreateWebSocket(TEXT("ws://127.0.0.1:8080"), TEXT("ws"));

    WebSocket->OnMessage().AddLambda([](const FString& Message)
    {
        // 여기서 실시간으로 날아오는 델타(Delta) JSON을 처리합니다.
        UE_LOG(LogTemp, Log, TEXT("웹소켓 실시간 업데이트: %s"), *Message);
    });

    WebSocket->Connect();
    UE_LOG(LogTemp, Warning, TEXT("초기 세팅 완료. 웹소켓 연결을 시도합니다."));
}

void AMyComboActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (WebSocket.IsValid() && WebSocket->IsConnected())
    {
        WebSocket->Close();
    }
    Super::EndPlay(EndPlayReason);
}

