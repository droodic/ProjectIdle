// Fill out your copyright notice in the Description page of Project Settings.


#include "MeetingDepartment.h"
#include "Idea.h"
#include "Components/WidgetComponent.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/Departments/ProgrammingDepartment.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "Widgets/MeetingDepWidget.h"
#include "Department.h"
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
	//GM->DepartmentList.Add(this);
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
	auto ChairIndex = 0;
	auto Index = 0;
	auto LoopCount = 0;

	auto ChairSize = GM->MeetingChairList.Num();
	auto EmployeeSize = GM->EmployeeList.Num();
	FString sizeString = FString::FromInt(EmployeeSize);
	GEngine->AddOnScreenDebugMessage(Index++, 3.f, FColor::Red, sizeString, true);

	bool MoreEmployeeThanChair = false;

	if (EmployeeSize > ChairSize)
	{
		//If there too many employee
		MoreEmployeeThanChair = true;
	}

	for (auto Dep : GM->DepartmentList) {
		//GEngine->AddOnScreenDebugMessage(Index++, 3.f, FColor::Red, "Loop through Deplist", true);

		if (Dep->HasSupervisor) {
			Dep->SupervisorRef->MoveEmployee(GM->MeetingChairList[ChairIndex++]->GetActorLocation());
			EmployeesAtMeetingList.Add(Dep->SupervisorRef);
			//GEngine->AddOnScreenDebugMessage(Index++, 5.f, FColor::Red, "Supervisor found");
			//break;
		}
		else if (!Dep->HasSupervisor) {
			if (!MoreEmployeeThanChair) {
				for (auto Emp : GM->EmployeeList) {
					if (Dep->DepRole == Emp->EmployeeRole) {
						EmployeesAtMeetingList.Add(Emp);
						Emp->MoveEmployee(GM->MeetingChairList[ChairIndex++]->GetActorLocation());
						//GEngine->AddOnScreenDebugMessage(Index++, 5.f, FColor::Red, "No supp- Sending employee");
					}
				}
			}
			else {
				//Debug Message to prevent crash, implement later
			}
		}
	}



}

void AMeetingDepartment::BackFromMeeting()
{
	auto Counter = EmployeesAtMeetingList.Num();

	if (!CanReturn) {
		for (auto Emp : EmployeesAtMeetingList) {
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
		for (auto Emp : EmployeesAtMeetingList) {

			Emp->MoveEmployee(Emp->StartPosition);
			EmployeesAtMeetingList.Remove(Emp);

		}

		for (auto Emp : GM->EmployeeList) {
			if (Emp->Position != EPosition::Supervisor) {
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
	}
}
