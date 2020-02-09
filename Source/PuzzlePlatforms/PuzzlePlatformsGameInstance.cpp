// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{	
	static ConstructorHelpers::FClassFinder<UMainMenu> Find_MenuClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(Find_MenuClass.Class != nullptr)) return;
	
	MenuClass = Find_MenuClass.Class;


}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor: %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);

	Menu->AddToViewport();

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!ensure(PC != nullptr)) return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputModeData);
	PC->bShowMouseCursor = true;

	Menu->MenuInterface = this;
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hosting (Reload)"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
