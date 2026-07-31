#include <gui/screen7_screen/Screen7View.hpp>

Screen7View::Screen7View() :
    currentStage(STAGE_1_PRIMING),
    currentCycle(1),
    secondsRemaining(60), // Start with 60 seconds for Priming
    tickCounter(0)
{
}

void Screen7View::setupScreen()
{
    Screen7ViewBase::setupScreen();

    // Link screen-level wildcard buffers straight to your widgets
    textPurgeCycle.setWildcard(cycleBuffer);
    textPurgeCountdown.setWildcard(countdownBuffer);

    textDetectionCycle.setWildcard(cycleBuffer);
    textScanCountdown.setWildcard(countdownBuffer);

    // Bootstrap system to the first stage
    initStage(STAGE_1_PRIMING);
}

void Screen7View::tearDownScreen()
{
    Screen7ViewBase::tearDownScreen();
}

// Automatically runs ~60 times per second
void Screen7View::handleTickEvent()
{   
    topStatusBar7.handleTickEvent();
    // If reach the success screen, stop counting frames
    if (currentStage == STAGE_3_SUCCESS)
    {
        return;
    }

    tickCounter++;
    
    // Smoothly animate the circular progress ring forward every frame
    float totalDuration = (currentStage == STAGE_1_PRIMING) ? 60.0f : 10.0f;
    float elapsedSeconds = totalDuration - ((float)secondsRemaining - ((float)tickCounter / 60.0f));
    int16_t progressPercent = (int16_t)((elapsedSeconds / totalDuration) * 100.0f);

    if (currentStage == STAGE_1_PRIMING)
    {
        Primingprogress.setValue(progressPercent);
        Primingprogress.invalidate();
    }
    else if (currentStage == STAGE_2_BUBBLE_DETECTION)
    {
        BubbleProgress.setValue(progressPercent);
        BubbleProgress.invalidate();
    }

    // Exactly once every 60 ticks (~1 real second), advance the timer
    if (tickCounter >= 60)
    {
        tickCounter = 0;
        handleStageTimers();
    }
}

// Logic framework to handle seconds, cycles, and stage swapping
void Screen7View::handleStageTimers()
{
    if (secondsRemaining > 0)
    {
        secondsRemaining--;
        updateStageUI();
    }

    // When a countdown clock strikes 0
    if (secondsRemaining == 0)
    {
        if (currentCycle == 1)
        {
            // Advance to Cycle 2 and restart countdown clock
            currentCycle = 2;
            secondsRemaining = (currentStage == STAGE_1_PRIMING) ? 60 : 10;
            updateStageUI();
        }
        else // Cycle 2 is completely finished!
        {
            if (currentStage == STAGE_1_PRIMING)
            {
                // Transition out of Priming into Bubble Detection
                initStage(STAGE_2_BUBBLE_DETECTION);
            }
            else if (currentStage == STAGE_2_BUBBLE_DETECTION)
            {
                // Transition out of Bubble Detection into Success window
                initStage(STAGE_3_SUCCESS);
            }
        }
    }
}

// Sets up structural values when transitioning to a new layout visibility state
void Screen7View::initStage(ValidationStage newStage)
{
    currentStage = newStage;
    currentCycle = 1;
    tickCounter = 0;

   
    stage1PrimingWidget1.setVisible(currentStage == STAGE_1_PRIMING);
    stage2BubbleWidget1.setVisible(currentStage == STAGE_2_BUBBLE_DETECTION);
    stage3SuccessWidget1.setVisible(currentStage == STAGE_3_SUCCESS);

    // Assign stage-specific time lengths
    if (currentStage == STAGE_1_PRIMING)
    {
        secondsRemaining = 60;
        topStatusBar7.setScreenTitle("Stage 1-Priming");
    }
    else if (currentStage == STAGE_2_BUBBLE_DETECTION)
    {
        secondsRemaining = 10;
        topStatusBar7.setScreenTitle("Stage 2-Bubble Detection");
    }
    else if (currentStage == STAGE_3_SUCCESS)
    {
        topStatusBar7.setScreenTitle(""); // <-- Pass empty string to make it completely blank!
    }

    // Force refresh screen layers
    updateStageUI();
    stage1PrimingWidget1.invalidate();
    stage2BubbleWidget1.invalidate();
    stage3SuccessWidget1.invalidate();
}

// Manages printing the live string data into buffers and invalidating text areas
void Screen7View::updateStageUI()
{
    // Format text data for the live cycle ratio text box
    Unicode::snprintf(cycleBuffer, 8, "%d / 2", currentCycle);

    // Format text data for standard MM:SS digital countdown clock layout
    Unicode::snprintf(countdownBuffer, 12, "00:%02d", secondsRemaining);

    // Target the active widget layout to force visual screen redraws
    if (currentStage == STAGE_1_PRIMING)
    {
        textPurgeCycle.invalidate();
        textPurgeCountdown.invalidate();
    }
    else if (currentStage == STAGE_2_BUBBLE_DETECTION)
    {
        textDetectionCycle.invalidate();
        textScanCountdown.invalidate();
    }
}

// Triggered automatically when the continue button on stage 3 is clicked
void Screen7View::btnContinueClicked()
{
    application().gotoScreen8ScreenNoTransition();
}