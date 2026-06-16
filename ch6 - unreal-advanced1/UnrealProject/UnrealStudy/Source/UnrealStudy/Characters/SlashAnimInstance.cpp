// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/SlashAnimInstance.h"
#include "Public\SlashCharactor.h"
#include "GameFramework/CharacterMovementComponent.h" // 캐릭터 무브먼트 활용
#include "Kismet/KismetMathLibrary.h" // 수학 계산 유틸리티(벡터 크기 계산 등)

void USlashAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // 이 애니메이션을 소유한 폰(Pawn)을 가져와 ASlashCharactor 타입으로 형변환(Cast)
    // 캐스팅에 성공하면(유효한 캐릭터라면) SlashCharacter 변수에 저장
    SlashCharacter = Cast<ASlashCharactor>(TryGetPawnOwner());
    
    // 캐릭터가 성공적으로 할당되었다면
    if(SlashCharacter)
    {
        // 매 프레임 속도를 구하기 위해, 캐릭터 내부의 무브먼트 컴포넌트를 미리 찾아 변수에 할당
        SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
    }
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    // 캐릭터의 무브먼트 컴포넌트가 정상적으로 캐싱되어 유효하다면
    if(SlashCharacterMovement)
    {   
        // 캐릭터의 3차원 속도(Velocity) 벡터 중 XY축(평면 이동) 데이터만 추출하여 1차원 길이(스칼라)값으로 변환한 뒤,
        // 애니메이션 블루프린트에서 읽어갈 수 있도록 GroundSpeed 변수에 할당
        GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);

        IsFalling = SlashCharacterMovement->IsFalling();
    }
}