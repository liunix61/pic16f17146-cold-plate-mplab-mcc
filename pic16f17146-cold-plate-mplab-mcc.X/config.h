#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

//Lowest allowed temperature in demo mode
#define DEMO_TEMP_LIMIT_LOW 5

//Maximum allowed temperature to set
#define TEMP_LIMIT_MAX 25
    
//Minimum Current Limit
#define CURRENT_LIMIT_MIN 1
    
//Threshold to detect power
//~100mA per bit
#define POWER_DETECT_MINIMUM 10
    
//Max Temperature before 100% Fan Speed
#define SAFETY_TEMP_MAX 60
    
//Sense Resistance
#define SENSE_RESISTANCE 0.01
    
//Resolution of the DAC (in terms of bits per volt)
//125 = 256 / 2.048V / 10
#define DAC_CURRENT_RES 125

//Pre-Computed DAC Formula
#define DAC_FORMULA_CONSTANT ((DAC_CURRENT_RES * SENSE_RESISTANCE) / 10.0)
    
//-- Default Values used for resetting EEPROM -- 
//Some settings are only accessible in developer mode
    
//Default Peltier Current Limit
#define DEFAULT_CURRENT_LIMIT 4
    
//Default Plate Set Point
#define DEFAULT_LAST_TEMP_SETTING 10
    
//Default Temperature Limits
#define DEFAULT_MAX_INT_SETTING 70
#define DEFAULT_MAX_HOT_SETTINGS 80
    
//Default Temperature Hysteresis
//Will turn off at SET_POINT + OVER and on again at SET_POINT + UNDER
#define DEFAULT_TEMP_HYSTER_OVER 5
#define DEFAULT_TEMP_HYSTER_UNDER 5
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */
