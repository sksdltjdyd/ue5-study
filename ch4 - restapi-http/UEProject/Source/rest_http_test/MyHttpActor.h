#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h" // Http 요청을 위해 필요
#include "Interfaces/IHttpResponse.h" // Http 응답을 위해 필요
#include "MyHttpActor.generated.h"

UCLASS()
class REST_HTTP_TEST_API AMyHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyHttpActor();

protected:
	virtual void BeginPlay() override;

public:	
	// 1. API에 데이터를 달라고 요청하는 함수
	void RequestUserData();

	// 2. 서버에서 데이터가 도착했을 때 실행될 콜백 함수 (답장 받는 곳)
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 공개환율 API 요청 함수
	void RequestExchangeRate();

	// 공개환율 API 응답 처리 함수
	void OnExchangeRateReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 날씨정보 API 요청 함수
	void RequestWeatherInfo();

	// 날씨정보 API 응답 처리 함수
	void OnWeatherInfoReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 데이터를 보내는 함수와 응답을 받는 콜백 선언
	void SendPlayerScore();
	void OnPostResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};