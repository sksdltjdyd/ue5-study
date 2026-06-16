// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

UCLASS()
class UNREALSTUDY_API USlashAnimInstance : public UAnimInstance
{
    GENERATED_BODY()
public:
    // 애니메이션 인스턴스가 처음 생성될 때 단 한 번 호출되는 초기화 함수
    // 일반 액터(Actor)의 BeginPlay()와 유사하게, 처음에 필요한 데이터나 포인터를 캐싱(저장)할 때 사용
    virtual void NativeInitializeAnimation() override;
    
    // 매 프레임마다 호출되어 애니메이션 상태나 변수들을 실시간으로 갱신하는 함수입
    // 일반 액터의 Tick() 함수와 유사한 역할을 하며, 여기서 플레이어의 속도나 상태를 지속적으로 체크
    virtual void NativeUpdateAnimation(float DeltaTime) override;

    // 이 애니메이션을 재생하고 있는 실제 캐릭터 액터의 포인터를 저장하는 변수
    // 매 프레임마다 캐릭터를 찾는(Cast) 비용을 줄이기 위해 Initialize 단계에서 미리 찾아옴
    UPROPERTY(BlueprintReadOnly, Category = "Component")
    class ASlashCharactor* SlashCharacter;

    // 캐릭터의 이동 정보(속도, 점프, 떨어짐 등)를 담당하는 무브먼트 컴포넌트 포인터
    // 캐릭터와 마찬가지로 성능을 위해 미리 캐싱해두고 사용
    UPROPERTY(BlueprintReadOnly, Category = "Component")
    class UCharacterMovementComponent* SlashCharacterMovement;
    
    // 애니메이션 블루프린트(블렌드 스페이스 등)에서 Idle/Walk/Run 애니메이션을 전환하는 기준으로 사용
    // 캐릭터의 현재 이동 속력(스칼라 값)을 저장하는 변수
    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    float GroundSpeed;

    // 애니메이션 블루프린트(블렌드 스페이스 등)에서 Jump 애니메이션을 전환하는 기준으로 사용
    // 캐릭터의 현재 상태(추락 상태)를 저장하는 변수
    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool IsFalling;
};