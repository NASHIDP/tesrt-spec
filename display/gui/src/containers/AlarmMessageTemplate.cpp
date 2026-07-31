#include <gui/containers/AlarmMessageTemplate.hpp>
#include <texts/TextKeysAndLanguages.hpp>

AlarmMessageTemplate::AlarmMessageTemplate()
    : cardID(-1)
{
}

void AlarmMessageTemplate::initialize()
{
    AlarmMessageTemplateBase::initialize();
    
    // 1. Clear local character buffers so they start clean
    titleBuffer[0] = '\0';
    descBuffer[0] = '\0';

    // 2. Bind the local RAM buffers to the wildcard widgets
    txtAlarmTitle.setWildcard(titleBuffer);
    txtAlarmDescription.setWildcard(descBuffer);

   
}
// Configures the card's visual identity when spawned
void AlarmMessageTemplate::setupAlarmCard(const char* titleStr, const char* descStr, touchgfx::colortype stripeColor)
{
    

    // 2. Set the color of the status accent stripe
    boxSeverityStripe.setColor(stripeColor);

    // 3. Copy character strings safely into our local widget buffers
    touchgfx::Unicode::strncpy(titleBuffer, titleStr, 32);
    touchgfx::Unicode::strncpy(descBuffer, descStr, 128);

    // 4. Force TouchGFX to repaint the modified visuals
    
    boxSeverityStripe.invalidate();
    txtAlarmTitle.invalidate();
    txtAlarmDescription.invalidate();
}


// Triggered when user hits Acknowledge
void AlarmMessageTemplate::acknowledgeClicked()
{
    
    AlarmMessageTemplateBase::acknowledgeClicked();
}

// Triggered when user hits Silence Alarm
void AlarmMessageTemplate::silenceClicked()
{
    
    AlarmMessageTemplateBase::silenceClicked();
}