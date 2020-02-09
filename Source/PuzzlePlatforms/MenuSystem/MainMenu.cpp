// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzlePlatformsGameInstance.h"

void UMainMenu::Setup(void)
{
	AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!ensure(PC != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputModeData);
	PC->bShowMouseCursor = true;

}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!ensure(PC != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PC->SetInputMode(InputModeData);

	PC->bShowMouseCursor = false;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!ensure(Success)) return Success;
	
	if (!ensure(Btn_Host != nullptr)) return false;
	Btn_Host->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);

	if (!ensure(Btn_Join != nullptr)) return false;
	Btn_Host->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClicked);

	return true;
}

void UMainMenu::OnHostClicked()
{
	if (ensure(MenuInterface != nullptr)) {
		MenuInterface->Host();
	}
}

void UMainMenu::OnJoinClicked(void)
{
	UPuzzlePlatformsGameInstance* GI = Cast<UPuzzlePlatformsGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!ensure(GI != nullptr)) return;

	GI->Join(TEXT("127.0.0.1"));
}
