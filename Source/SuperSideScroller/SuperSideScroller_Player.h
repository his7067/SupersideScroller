// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
    
    GENERATED_BODY()

    public: 
        ASuperSideScroller_Player();
    
    protected:
      
        virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
        void Sprint();
        void StopSprinting();
        void Move(const FInputActionValue& Value);
        void ThrowProjectile();

        UPROPERTY(EditAnywhere, Category = "Input")
        class UInputMappingContext* IC_Character;
        UPROPERTY(EditAnywhere, Category = "Input")
        class UInputAction* IA_Sprint;
        UPROPERTY(EditDefaultsOnly, Category = "Input")
        TObjectPtr<class UInputAction> IA_Move;
        UPROPERTY(EditDefaultsOnly, Category = "Input")
        TObjectPtr<class UInputAction> IA_Throw; // UInputAction 변수 선언
        /** 점프 입력 액션 */
        UPROPERTY(EditDefaultsOnly, Category = "Input")
        TObjectPtr<class UInputAction> IA_Jump;
    private:
    
        bool bIsSprinting;
        //기본적으로 전력 질주 동작을 false로 설정
       
   
};