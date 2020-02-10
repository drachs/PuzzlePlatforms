// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void ToggleInGameMenu();

	UFUNCTION(Exec)
	void Host() override;
		
	UFUNCTION(Exec)
	void Join(const FString& Address) override;

private:
	UPROPERTY()
	class UInGameMenu* InGameMenu = nullptr;

	TSubclassOf<class UMainMenu> MenuClass;

	TSubclassOf<class UInGameMenu> InGameMenuClass;
};
