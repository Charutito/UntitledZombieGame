#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    CurrentDelay = RestartDelay;

    if (bIsWinner)
    {
        CreateScreenWidget(WinScreenClass);
    }
    else
    {
        CreateScreenWidget(LoseScreenClass);
    }

    FTimerHandle DelayCountDownTimer;
    GetWorldTimerManager().SetTimer(DelayCountDownTimer, this, &AShooterPlayerController::RestartCountDown, 1.f, true, 0.0);
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::RestartCountDown()
{
    if (CurrentDelay != 0)
    {
        CurrentDelay = CurrentDelay - 1;
    }
}

void AShooterPlayerController::CreateScreenWidget(TSubclassOf<class UUserWidget> ScreenClass)
{
    UUserWidget* WidgetScreen = CreateWidget(this, ScreenClass);
    if (WidgetScreen != nullptr)
    {
        WidgetScreen->AddToViewport();
    }
}
