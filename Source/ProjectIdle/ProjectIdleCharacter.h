// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "GameFramework/Character.h"
#include "ProjectIdleCharacter.generated.h"

UCLASS(Blueprintable)
class AProjectIdleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProjectIdleCharacter();

	class UGameManager* GM;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		int32 Money = 2000;

	UPROPERTY(BlueprintReadOnly)
		FString FTxtMoney;

	UPROPERTY(BlueprintReadOnly)
		class UTextBlock* MoneyText;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UGameUI> WidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UAnimMontage* HelpAnimation;



	UPROPERTY()
		APlayerController* PlayerControl;

	UPROPERTY()
		float CameraMovementSpeed = 4.5;

	UPROPERTY()
		int32 ScreenSizeX;

	UPROPERTY()
		int32 ScreenSizeY;

	bool OutOfBound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor") int CurrentFloor = 1;


	UFUNCTION()
		FVector GetCameraPanDirection();

	UFUNCTION()
		void PlayHelpAnim();

	UFUNCTION() void ResumeMovement();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;



	int32 TotalMoney;
};

