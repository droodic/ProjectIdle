// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "ProjectIdle/Employees/Employee.h"
#include "EmployeeSheetWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UEmployeeSheetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class AEmployee* Employee;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Promote_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Fire_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Action_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Action_BtnTxt;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* FaceImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* EmployeeName_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* EmployeeRole_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UHorizontalBox* Performance_Box;

	UPROPERTY(BlueprintReadWrite) ERole EmployeeRole;
	UPROPERTY(BlueprintReadWrite) EPosition EmployeePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Morale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Salary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Performance;

public:
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void Promote();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void Fire();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void PerformAction();

	UFUNCTION(BlueprintCallable, Category = "Converters") FText RoleToText(enum ERole role);
	UFUNCTION(BlueprintGetter, Category = "Converters") FText PositionToText(enum EPosition position);
	UFUNCTION(BlueprintGetter, Category = "Converters") FText SalaryToText(float salar);

private:
	virtual void NativeConstruct() override;
};
