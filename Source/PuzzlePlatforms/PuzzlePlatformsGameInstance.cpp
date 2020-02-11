// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{	
	static ConstructorHelpers::FClassFinder<UMainMenu> Find_MenuClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(Find_MenuClass.Class != nullptr)) return;	
	MenuClass = Find_MenuClass.Class;

	static ConstructorHelpers::FClassFinder<UInGameMenu> Find_InGameMenuClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(Find_InGameMenuClass.Class != nullptr)) return;
	InGameMenuClass = Find_InGameMenuClass.Class;

}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor: %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->MenuInterface = this;
	Menu->Setup();
}

void UPuzzlePlatformsGameInstance::ToggleInGameMenu()
{
	if (!InGameMenu) {
		if (!ensure(InGameMenuClass != nullptr)) return;
		InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
		if (!ensure(InGameMenu != nullptr)) return;
	}

	InGameMenu->Toggle();
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hosting (Reload)"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::MainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MenuLevel", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand(TEXT("quit"));
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
