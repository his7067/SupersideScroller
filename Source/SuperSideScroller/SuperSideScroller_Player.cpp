// SuperSideScroller_Player.cpp (최종 수정된 코드)


#include "SuperSideScroller_Player.h"
// 새로 추가된 헤더 (Enhanced Input Subsystem 및 LocalPlayer 접근에 필요)
#include "GameFramework/PlayerController.h" 
#include "Engine/LocalPlayer.h" 

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ASuperSideScroller_Player::ASuperSideScroller_Player()
{
    // 생성 시 기본적으로 전력 질주 상태가 아님을 보장
    bIsSprinting = false;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // 1. Super 키워드를 사용해 부모 클래스의 함수를 호출하는 것이 좋습니다.
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 2. 필요한 포인터들을 가져오면서 유효성을 한 번에 확인합니다.
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        // 3. LocalPlayer Subsystem을 가져옵니다. (ULocalPlayer::GetSubsystem 사용)
        if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // 4. EnhancedInputComponent를 가져옵니다.
            if (UEnhancedInputComponent* EnhancedPlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
            {
                // 5. 모든 것이 유효할 때만 매핑과 바인딩을 수행합니다.
                if (IA_Throw) // IA_Throw 에셋이 할당되었는지 확인
                {
                    EnhancedPlayerInput->BindAction(
                        IA_Throw,
                        ETriggerEvent::Triggered, // 키를 누르는 순간 이벤트 발생
                        this,
                        &ASuperSideScroller_Player::ThrowProjectile
                    );
                }
                if (IA_Jump)
                {
                    // 키를 눌렀을 때 Jump() 함수 호출 (점프 시작)
                    EnhancedPlayerInput->BindAction(
                        IA_Jump,
                        ETriggerEvent::Started, // 키를 누르기 시작했을 때
                        this,
                        &ACharacter::Jump  // ACharacter::Jump 함수에 연결
                    );

                    // 키를 떼었을 때 StopJumping() 함수 호출 (점프 종료 로직, 선택 사항)
                    EnhancedPlayerInput->BindAction(
                        IA_Jump,
                        ETriggerEvent::Completed, // 키 누름이 완료되었을 때
                        this,
                        &ACharacter::StopJumping // ACharacter::StopJumping 함수에 연결
                    );
                }
                // 매핑 컨텍스트 추가
                EnhancedSubsystem->AddMappingContext(IC_Character, 1);

                // Sprint 입력 액션의 누름 이벤트를 Sprint 함수에 바인딩합니다
                EnhancedPlayerInput->BindAction(IA_Sprint,
                    ETriggerEvent::Triggered, this,
                    &ASuperSideScroller_Player::Sprint);

                // Sprint 입력 액션의 해제 이벤트를 StopSprinting 함수에 바인딩합니다
                EnhancedPlayerInput->BindAction(IA_Sprint,
                    ETriggerEvent::Completed, this,
                    &ASuperSideScroller_Player::StopSprinting);

                // 기본 이동 입력 액션 바인딩
                EnhancedPlayerInput->BindAction(IA_Move,
                    ETriggerEvent::Triggered, this,
                    &ASuperSideScroller_Player::Move);
            }
        }
    }
}


void ASuperSideScroller_Player::Move(const FInputActionValue& Value)
{
    // Vector2D 형태로 입력 값을 가져옵니다.
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // Character 클래스를 사용한다고 가정하고, 움직임 입력을 추가합니다.
        // MovementVector.X는 오른쪽/왼쪽 이동입니다.
        AddMovementInput(GetActorRightVector(), MovementVector.X);

        // MovementVector.Y는 앞/뒤 이동입니다 (사이드 스크롤러에서는 보통 사용되지 않음).
        // AddMovementInput(GetActorForwardVector(), MovementVector.Y);
    }
}

// 6. ThrowProjectile() 함수 정의
void ASuperSideScroller_Player::ThrowProjectile()
{
    // 성공적인 호출을 알리는 로그 메시지 출력
    UE_LOG(LogTemp, Warning, TEXT("ThrowProjectile() successfully called!"));

    // 이 곳에 실제 투사체 발사 로직을 구현하게 됩니다.
}

void ASuperSideScroller_Player::Sprint()
// ... (Sprint 함수 내용은 변경 없음)
{
    if (!bIsSprinting)
    {
        bIsSprinting = true;
        if (GetCharacterMovement())
        {
            GetCharacterMovement()->MaxWalkSpeed = 500.0f;
        }
    }
}

void ASuperSideScroller_Player::StopSprinting()
// ... (StopSprinting 함수 내용은 변경 없음)
{
    if (bIsSprinting)
    {
        bIsSprinting = false;
        if (GetCharacterMovement())
        {
            GetCharacterMovement()->MaxWalkSpeed = 300.0f;
        }
    }
}