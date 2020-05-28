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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* EmployeeName_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* EmployeeRole_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* EmployeePosition_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Morale_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Salary_T;
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Performance_T;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Promote_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Fire_Btn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EmployeeRole;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Morale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Performance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Salary;
	
public:
	void Promote();
	void Fire();

	FText RoleToText(enum ERole role);
	FText PositionToText(enum EPosition position);

private:
	virtual void NativeConstruct() override;
};
