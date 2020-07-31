// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Engine.h"
#include "Widgets/MoneyWidget.h"
#include "Widgets/EmployeeSheetWidget.h"
#include "Employees/FloorManager.h"
#include "Employees/Supervisor.h"
#include "UObject/ConstructorHelpers.h"

AGameHUD::AGameHUD()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> NotificationSoundCue(TEXT("SoundCue'/Game/Sounds/NotificationCue.NotificationCue'"));
	if (NotificationSoundCue.Succeeded())
	{
		NotificationSound = NotificationSoundCue.Object;
		NotificationAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("NotificationAudio"));
		NotificationAudio->SetSound(NotificationSound);
		NotificationAudio->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> FootStepCue(TEXT("SoundCue'/Game/Sounds/FootstepCue.FootstepCue'"));
	if (FootStepCue.Succeeded())
	{
		FootStepSound = NotificationSoundCue.Object;
		FootStepAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("FootStepAudio"));
		FootStepAudio->SetSound(FootStepSound);
		FootStepAudio->bAutoActivate = false;
	}


}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GM = GetWorld()->GetGameInstance<UGameManager>();

	if (MoneyWidgetClass)
	{
		MoneyWidget = CreateWidget<UMoneyWidget>(UGameplayStatics::GetPlayerController(this, 0), MoneyWidgetClass);

		if (MoneyWidget)
		{
			MoneyWidget->AddToViewport();
		}
	}
	if (EmployeeSheetClass != nullptr)
	{
		EmpSheetWidget = CreateWidget<UEmployeeSheetWidget>(UGameplayStatics::GetPlayerController(this, 0), EmployeeSheetClass);
	}

	//if (WorkstationClass)
	//{
	//	WorkstationWidget = CreateWidget<UWorkstationUpgradeWidget>(UGameplayStatics::GetPlayerController(this, 0), WorkstationClass);
	//}
}

void AGameHUD::ShowEmployeeSheet(class AEmployee* employee)
{
	if (!EmpSheetWidget->IsInViewport() && EmpSheetWidget != nullptr && EmpSheetWidget->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Showing Employee Sheet"));

		employee->IsDisplaying = true;

		EmpSheetWidget->Employee = employee;
		EmpSheetWidget->EmployeeName_T->Text = employee->EmployeeName;
		EmpSheetWidget->EmployeeRole_T->Text = EmpSheetWidget->RoleToText(employee->EmployeeRole);
		EmpSheetWidget->EmployeePosition = employee->Position;
		EmpSheetWidget->Salary = employee->Salary;
		//employee->FaceCamera->CaptureScene();
		if (!employee->FaceCamera->IsActive()) {
			employee->FaceCamera->Activate();
			employee->FaceCamera->SetVisibility(true);
		}

		//EmpSheetWidget->FaceImage->SetBrushFromTexture(employee->FaceCamera->TextureTarget);

		if (Cast<AFloorManager>(EmpSheetWidget->Employee) == nullptr && Cast<ASupervisor>(EmpSheetWidget->Employee) == nullptr) {
			EmpSheetWidget->Promote_Btn->SetVisibility(ESlateVisibility::Visible);
			EmpSheetWidget->Fire_Btn->SetVisibility(ESlateVisibility::Visible);
			EmpSheetWidget->Morale = employee->Morale;
			EmpSheetWidget->Performance = employee->Performance;
		}
		else if (Cast<ASupervisor>(EmpSheetWidget->Employee) != nullptr) {
			EmpSheetWidget->Promote_Btn->SetVisibility(ESlateVisibility::Hidden);
			EmpSheetWidget->Fire_Btn->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			EmpSheetWidget->Promote_Btn->SetVisibility(ESlateVisibility::Hidden);
			EmpSheetWidget->Fire_Btn->SetVisibility(ESlateVisibility::Hidden);
		}

		if (employee->HasBeenEvaluated) {
			EmpSheetWidget->Performance_Box->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			EmpSheetWidget->Performance_Box->SetVisibility(ESlateVisibility::Hidden);
		}

		if (Cast<ASupervisor>(employee) != nullptr) {
			EmpSheetWidget->Action_Btn->SetVisibility(ESlateVisibility::Visible);
			EmpSheetWidget->Action_BtnTxt->SetText(FText::FromString("Evaluate"));
		}
		else if (Cast<AFloorManager>(employee) != nullptr) {
			EmpSheetWidget->Action_Btn->SetVisibility(ESlateVisibility::Visible);
			EmpSheetWidget->Action_BtnTxt->SetText(FText::FromString("Manage"));
		}
		else {
			EmpSheetWidget->Action_Btn->SetVisibility(ESlateVisibility::Hidden);
		}

		GM->IsWidgetInDisplay = true;
		GM->CurrentWidgetInDisplay = EmpSheetWidget;
		EmpSheetWidget->AddToViewport();
	}
}

void AGameHUD::RefreshEmployeeSheet(AEmployee* employee)
{
	EmpSheetWidget->EmployeePosition = employee->Position;
	EmpSheetWidget->Salary = employee->Salary;
	EmpSheetWidget->Morale = (int)employee->Morale;
}

void AGameHUD::ShowWidget(UUserWidget* Widgetc, TSubclassOf<UUserWidget> WidgetClass)
{
	//auto UseClass = Widgetc;
		//Widgetc->RemoveFromViewport();
	if (Widgetc != nullptr && Widgetc->IsValidLowLevel()) 
	{
		Widgetc->AddToViewport();
	}
	else 
	{
		auto NewWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), WidgetClass);
		NewWidget->AddToViewport();
	}
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

//void AGameHUD::UpdateMoney(int32 Value)
//{
//	if (MoneyWidget)
//	{
//		MoneyWidget->UpdateMoney(Value);
//	}
//}


void AGameHUD::CloseEmployeeSheet()
{
	EmpSheetWidget->RemoveFromViewport();
}

void AGameHUD::ShowStationUpgrade(class AWorkstation* station)
{
	//if (!WorkstationWidget->IsInViewport())
	//{
	//	WorkstationWidget->AddToViewport();
	//}
	//else
	//{
	//	WorkstationWidget->RemoveFromViewport();
	//}
}

void AGameHUD::PlayNotification()
{
	NotificationAudio->Play();
}

void AGameHUD::WalkingSound(bool IsWalking)
{
	if (IsWalking && FootStepAudio)
	{
		FootStepAudio->Play();
	}
	if (!IsWalking && FootStepAudio)
	{
		FootStepAudio->Stop();
	}
}