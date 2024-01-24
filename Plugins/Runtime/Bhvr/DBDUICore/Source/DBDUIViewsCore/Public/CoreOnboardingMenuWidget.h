#pragma once

#include "CoreMinimal.h"
#include "ChangeAccountActionDelegate.h"
#include "QuitGameActionDelegate.h"
#include "OnboardingMenuViewInterface.h"
#include "MenuTabSelectedAgainDelegate.h"
#include "CoreBaseUserWidget.h"
#include "SettingsActionDelegate.h"
#include "BackActionDelegate.h"
#include "OnboardingMenuTabSelectedDelegate.h"
#include "CoreOnboardingMenuWidget.generated.h"

class UCoreTabContainerWidget;
class UCoreOnboardingMenuTitleWidget;
class UCoreInputSwitcherWidget;
class UCoreSelectableButtonWidget;
class UCoreFooterInputSwitcherWidget;

UCLASS(EditInlineNew)
class DBDUIVIEWSCORE_API UCoreOnboardingMenuWidget : public UCoreBaseUserWidget, public IOnboardingMenuViewInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Export)
	UCoreTabContainerWidget* OnboardingMenuTabs;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreOnboardingMenuTitleWidget* MenuTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* BackInputSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreFooterInputSwitcherWidget* SettingsInputSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreFooterInputSwitcherWidget* QuitGameInputSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCoreInputSwitcherWidget* ChangeAccountInputSwitcher;

private:
	UPROPERTY()
	FBackActionDelegate BackActionDelegate;

	UPROPERTY()
	FSettingsActionDelegate SettingsActionDelegate;

	UPROPERTY()
	FQuitGameActionDelegate QuitGameActionDelegate;

	UPROPERTY()
	FChangeAccountActionDelegate ChangeAccountActionDelegate;

	UPROPERTY()
	FOnboardingMenuTabSelectedDelegate MenuTabSelectedDelegate;

	UPROPERTY()
	FMenuTabSelectedAgainDelegate MenuTabSelectedAgainDelegate;

private:
	UFUNCTION(BlueprintCallable)
	void SetTitleText(const bool isInTutorial);

	UFUNCTION(BlueprintCallable)
	void SetBackButton(const bool isFTUE);

	UFUNCTION()
	void OnMenuTabSelectedAgain(UCoreSelectableButtonWidget* selectedButton);

	UFUNCTION()
	void OnMenuTabSelected(UCoreSelectableButtonWidget* selectedButton);

public:
	UCoreOnboardingMenuWidget();
};

FORCEINLINE uint32 GetTypeHash(const UCoreOnboardingMenuWidget) { return 0; }
