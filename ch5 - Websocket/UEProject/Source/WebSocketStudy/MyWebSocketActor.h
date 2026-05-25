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

private:
	// 웹소켓 객체
	// 객체를 안전하게 보관할 스마트 포인터
	TSharedPtr<IWebSocket> WebSocket; 

protected:
	// Sets default values for this actor's properties
	AMyWebSocketActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
