// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashCharactor.h"
#include "Components/InputComponent.h" // 인풋 컴포넌트 값 헤더 추가
#include "EnhancedInputComponent.h" // 향상된 입력 컴포넌트 헤더 추가
#include "EnhancedInputSubsystems.h" // 향상된 입력 서브시스템 헤더 추가
#include "GameFramework/PlayerController.h" // 플레이어 컨트롤러 헤더 추가
#include "Camera/CameraComponent.h" // 카메라 컴포넌트 헤더 추가
#include "GameFramework/SpringArmComponent.h" // 스프링 암 컴포넌트 헤더 추가

ASlashCharactor::ASlashCharactor()
{
 	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // 플레이어 입력 자동 수신 설정

	// 스프링 암 컴포넌트 생성 및 캡슐 컴포넌트에 부착
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f; // 카메라와의 거리 설정
	CameraBoom->bUsePawnControlRotation = true; // 폰의 회전에 따라 스프링 암이 회전하도록 설정

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 스프링 암에 카메라 부착

}

void ASlashCharactor::BeginPlay()
{
	Super::BeginPlay();

	// 입력 매핑 컨텍스트가 설정되어 있는지 확인
	// 플레이어 컨트롤러를 가져와서 입력 매핑 컨텍스트를 추가
	if (APlayerController* UnrealStudyPlayerController = Cast<APlayerController>(GetController()))
	{
		// 입력 매핑 컨텍스트를 플레이어 컨트롤러에 추가
		// UEnhancedInputLocalPlayerSubsystem을 사용하여 입력 매핑 컨텍스트를 추가
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(UnrealStudyPlayerController->GetLocalPlayer()))
		{
			// 입력 매핑 컨텍스트를 추가하여 입력을 처리할 수 있도록 설정
			Subsystem->AddMappingContext(SlashMappingContext, 0);
		}		
	}
}

// 입력 액션에 대한 처리 함수 구현
void ASlashCharactor::Movement(const FInputActionValue& Value)
{
	// 입력 액션에서 벡터 값을 가져와서 이동에 사용
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FVector Forward = GetActorForwardVector();
	const FVector Right = GetActorRightVector();

	if (Controller != nullptr)
    {
        // 이동 컴포넌트에게 해당 방향으로 움직이라고 명령
        AddMovementInput(Forward, MovementVector.Y);

		// 이동 컴포넌트에게 해당 방향으로 움직이라고 명령
        AddMovementInput(Right, MovementVector.X);
    }
}

// Look 액션에 대한 처리 함수 구현
void ASlashCharactor::Look(const FInputActionValue& Value)
{
	// 입력 액션에서 FVector2D 값을 가져와서 카메라 회전에 사용
	const FVector2D LookValue = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// 카메라 회전을 위한 로직
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}	
}

// Jump 액션에 대한 처리 함수 구현
void ASlashCharactor::DoJump(const FInputActionValue& Value)
{
    const bool bIsPressed = Value.Get<bool>();
    if (bIsPressed)
    {
        // 부모 클래스(ACharacter)의 기본 점프 실행
        ACharacter::Jump(); 
    }
}

void ASlashCharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 향상된 입력 시스템을 사용하여 입력 액션과 처리 함수를 바인딩
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 입력 액션과 처리 함수를 바인딩하여 입력을 처리할 수 있도록 설정
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharactor::Movement);
		// Look 액션과 처리 함수를 바인딩하여 회전을 처리할 수 있도록 설정
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharactor::Look);
		// Rotate 액션과 처리 함수를 바인딩하여 회전을 처리할 수 있도록 설정
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharactor::DoJump);
	}

}
