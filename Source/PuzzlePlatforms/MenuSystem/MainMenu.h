// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	IMenuInterface* MenuInterface;

	/**
	 * Display the Menu
	 */
	void Setup(void);

protected:
	/**
	 * Called by the engine when the Level is changed
	 */
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	/**
	 * Called by the game some point after construction
	 */
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Join_Cancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Join_Join;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Input_IPAddress;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnJoinClicked();
	
	UFUNCTION()
	void OnJoinJoinClicked();

	UFUNCTION()
	void OnJoinCancelClicked();


	
};
