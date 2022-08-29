#include "UI.h"

//Current UI State
static UI_STATE UI_state = STANDBY;
//Signals the UI has entered a new state
static bool UI_new_state = true;

UI_STATE UI_getState(void){
    return UI_state;
}

//UI State setter & flags a new state
void UI_setState(UI_STATE new_state){
    UI_state = new_state;
    UI_new_state = true;
}

//Updates the scene elements & sets a new scene if needed
void UI_refresh(void){
    if(UI_new_state){
        UI_setup();
        UI_new_state = false;
    }
    UI_update();
}

// when in a UI state, this handles reading encoder input, updating only the
// needed info on the OLED, and moving to the next UI state
void UI_handleStateInput(UI_STATE exit_state, void (*ui_update)(int16_t)){
    static bool pressed = false; // Value to keep track of button state, avoids blocking
    if(!BUTTON_GetValue()){ // button press means move to different UI state
        pressed = true;
    } else if(BUTTON_GetValue() && pressed == true){ // wait for button to be released
        UI_updateEEPROM();
        UI_setState(exit_state); // set state
        pressed = false;
    } else {
        (*ui_update)(encoderControl_getMoves());
    }
}

//Fill OLED with new static state data when the state is switched
void UI_setup(void){
    switch(UI_state){
        case STANDBY:
            settingMenus_standbySetup();
            break;
        case MENU:
            navMenu_setup();
            break;
        case RUNNING:
            runningMenus_runningSetup();
            break;
        case ERROR:
            break;
        case SET_TEMPERATURE:
            settingMenus_temperatureSetup();
            break;
        case CHANGE_UNITS:
            settingMenus_changeUnitsSetup();
            break;
        case LIMIT_CURRENT:
            settingMenus_currentSetup();
            break;
        case ABOUT:
            settingMenus_aboutSetup();
            break;
        case DEMO_MODE_TOGGLE:
            settingMenus_demoModeToggleSetup();
            break;
        case START:
            settingMenus_startSetup();
            break;
    }
}

//Update only the needed elements in a scene
void UI_update(void){
    switch(UI_state){
    case STANDBY:
        UI_handleStateInput(MENU, settingMenus_standbyUpdate);
        break;
    case MENU:
        UI_handleStateInput(navMenu_getSelected(), navMenu_update);
        break;
    case SET_TEMPERATURE:
        UI_handleStateInput(MENU, settingMenus_temperatureUpdate);
        break;
    case CHANGE_UNITS:
        UI_handleStateInput(MENU, settingMenus_changeUnitsUpdate);
        break;
    case START:
        UI_handleStateInput(RUNNING, settingMenus_startUpdate);
        break;
    case LIMIT_CURRENT:
        UI_handleStateInput(MENU, settingMenus_currentUpdate);
        break;
    case ABOUT:
        UI_handleStateInput(MENU, settingMenus_aboutUpdate);
        break;
    case RUNNING:
        UI_handleStateInput(STANDBY, runningMenus_runningUpdate);
        break;
    case DEMO_MODE_TOGGLE:
        UI_handleStateInput(MENU, settingMenus_demoModeToggleUpdate);
        break;
    case ERROR: // NO IMPLEMENTATION YET
        break;
    }
}

//Check if current value is different than what is in EEPROM
void UI_updateEEPROM(void){
    bool changed = false;
    if(settings_getSetting(SETTINGS_LAST_SET_TEMP) != (uint8_t)settingMenus_getTargetTemp()){
        settings_writeValue(SETTINGS_LAST_SET_TEMP, (uint8_t)settingMenus_getTargetTemp());
        changed = true;
    }
    if(settings_getSetting(SETTINGS_CURRENT_LIMIT) != settingMenus_getCurrentLimit()){
        settings_writeValue(SETTINGS_CURRENT_LIMIT, settingMenus_getCurrentLimit());
        changed = true;
    }
    if(settings_getSetting(SETTINGS_TEMP_UNIT) != settingMenus_getTempUnit()){
        settings_writeValue(SETTINGS_TEMP_UNIT, settingMenus_getTempUnit());
        changed = true;
    }
    if(settings_getSetting(SETTINGS_DEMO_MODE) != settingMenus_getDemoMode()){
        settings_writeValue(SETTINGS_DEMO_MODE, settingMenus_getDemoMode());
        changed = true;
    }
    
    if(changed){
        settings_writeCRC();
    }
}