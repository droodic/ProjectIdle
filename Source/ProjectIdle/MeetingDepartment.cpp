// Fill out your copyright notice in the Description page of Project Settings.


#include "MeetingDepartment.h"
#include "Idea.h"
#include "Components/WidgetComponent.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "Widgets/MeetingDepWidget.h"
#include "Employees/Artist.h"
#include "Employees/Programmer.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectIdle/Widgets/IdeaBacklogWidget.h"

// Sets default values
AMeetingDepartment::AMeetingDepartment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OfficeLocation = FVector(-720.0, 900, 200);
}

// Called when the game starts or when spawned
void AMeetingDepartment::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->MeetingDepartment = this;
	//temp assign, need to change class name , maybe move functions to gm
	UWorld* world = GetWorld();
	if (UserWidget != nullptr)
	{
		MeetingWidget = CreateWidget<UMeetingDepWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidget);
	}
}

void AMeetingDepartment::TakeIdea(Idea* SentIdea)
{
	CurrentIdea = SentIdea;
	
	if (MeetingWidget != nullptr && UserWidget != nullptr && SentIdea != nullptr) {
		MeetingWidget->I_GameCover->SetColorAndOpacity(SentIdea->CoverColor);
		MeetingWidget->T_GameTitle->SetText(FText::FromString(SentIdea->IdeaName));
		MeetingWidget->T_Genre->SetText(Idea::GenreToText(SentIdea->Genre));
		MeetingWidget->T_GameDescription->SetText(FText::FromString(SentIdea->IdeaDescription));
		MeetingWidget->T_SuccessChance->SetText(FText::AsPercent(SentIdea->SuccessChance / 100.f));
		MeetingWidget->T_Weight->SetText((SentIdea->ProgrammerWorkload > SentIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));
		
		if (SentIdea->ProgrammerWorkload == SentIdea->ArtistWorkload)
		{
			MeetingWidget->T_Weight->SetText(FText::FromString("All"));
		}
		GEngine->AddOnScreenDebugMessage(105, 5.f, FColor::Red, "Idea Transferred");
	}
	else if (MeetingWidget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(105, 5.f, FColor::Red, "NULPTR meetingwidget");
	}
	else if (UserWidget == nullptr) {
		GEngine->AddOnScreenDebugMessage(105, 5.f, FColor::Red, "NULPTR userwidget");
	}
	//MeetingWidget->AddToViewport();
}

void AMeetingDepartment::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	{
		MeetingWidget->AddToViewport();
	}
}
void AMeetingDepartment::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	{
		MeetingWidget->RemoveFromViewport();
	}
}

// Called every frame
void AMeetingDepartment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeetingDepartment::MoveToMeeting()
{
	int32 chairSize = GM->MeetingChairList.Num();
	int32 employeeSize = GM->EmployeeList.Num();
	int32 LoopUntil;
	FString sizeString = FString::FromInt(employeeSize);

	CanReturn = false;
	bool MoreEmployeeThanChair = false;

	if (chairSize > employeeSize)
	{
		LoopUntil = employeeSize;
	}
	else if (employeeSize > chairSize)
	{
		//If there too many employee
		MoreEmployeeThanChair = true;
		LoopUntil = employeeSize;
	}
	else
	{
		LoopUntil = chairSize;
	}

	for (int i = 0; i < LoopUntil; i++)
	{
		if (MoreEmployeeThanChair)
		{
			if (i < chairSize)
			{
				GM->EmployeeList[i]->MoveEmployee(GM->MeetingChairList[i]->GetActorLocation());
			}
			else
			{
				GM->EmployeeList[i]->MoveEmployee(OfficeLocation);
			}
		}
		else
		{
			GM->EmployeeList[i]->MoveEmployee(GM->MeetingChairList[i]->GetActorLocation());
		}
	}
}

void AMeetingDepartment::BackFromMeeting()
{
	//int32 employeeSize = GM->EmployeeList.Num();

	//Call a second time in case, they had no workstation on hire
	//GM->WorkStation->TestFunction();
	auto Counter = GM->EmployeeList.Num();

	if (!CanReturn) {
		for (auto Emp : GM->EmployeeList) {
			if (Emp->AI->IsMoving) {
				GEngine->AddOnScreenDebugMessage(999, 5.f, FColor::Green, "Employee moving, breaking");
				break;
			}
			else {
				GEngine->AddOnScreenDebugMessage(998, 5.f, FColor::Green, "Employee in chair, counter down");
				Counter--;
			}
		}
		if (Counter == 0) {
			GEngine->AddOnScreenDebugMessage(997, 5.f, FColor::Green, "CanReturn");
			CanReturn = true;
		}
	}

	if (CanReturn) {
		for (auto Emp : GM->EmployeeList) {

			Emp->MoveEmployee(Emp->StartPosition);
			//GM->EmployeeList[i]->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GM->EmployeeList[i]->GetActorLocation(), GM->EmployeeList[i]->StartPosition));
			//GM->EmployeeList[i]->

			//Assign workload test - move to own function/clean up later, also needs to be called when are at their workstation not before
			if (Emp->EmployeeRole == ERole::Artist)
			{
				Emp->AssignedWorkload = CurrentIdea->ArtistWorkload / GM->NumOfArtists;
				Emp->CurrentWorkload = Emp->AssignedWorkload;
				Emp->BeginWork();
			}
			else if (Emp->EmployeeRole == ERole::Programmer)
			{
				Emp->AssignedWorkload = CurrentIdea->ProgrammerWorkload / GM->NumOfProgrammers;
				Emp->CurrentWorkload = Emp->AssignedWorkload;
				Emp->BeginWork();
			}
		}
	}
	
	auto backlogWidget = GM->OfficeDepartment->BacklogWidget;
	backlogWidget->IdeaScrollBox->RemoveChild(Cast<UWidget>(CurrentIdea->IdeaButton));
	GM->OfficeDepartment->ideasGenerated--;

	/*for (int i = 0; i < employeeSize; i++)
	{
		if (!GM->EmployeeList[i]->AI->IsMoving) {
			GM->EmployeeList[i]->MoveEmployee(GM->EmployeeList[i]->StartPosition);
			//GM->EmployeeList[i]->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GM->EmployeeList[i]->GetActorLocation(), GM->EmployeeList[i]->StartPosition));
			//GM->EmployeeList[i]->

			//Assign workload test - move to own function/clean up later, also needs to be called when are at their workstation not before
			if (GM->EmployeeList[i]->EmployeeRole == ERole::Artist)
			{
				GM->EmployeeList[i]->AssignedWorkload = CurrentIdea->ArtistWorkload / GM->NumOfArtists;
				GM->EmployeeList[i]->CurrentWorkload = GM->EmployeeList[i]->AssignedWorkload;
				GM->EmployeeList[i]->BeginWork();
			}
			else if (GM->EmployeeList[i]->EmployeeRole == ERole::Programmer)
			{
				GM->EmployeeList[i]->AssignedWorkload = CurrentIdea->ProgrammerWorkload / GM->NumOfProgrammers;
				GM->EmployeeList[i]->CurrentWorkload = GM->EmployeeList[i]->AssignedWorkload;
				GM->EmployeeList[i]->BeginWork();
			}
		}
		
	}*/
}
