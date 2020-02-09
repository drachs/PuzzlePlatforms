// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzlePlatformsGameInstance.h"

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
