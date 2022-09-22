#ifndef DEFAULTS_H
#define	DEFAULTS_H

#ifdef	__cplusplus
extern "C" {
#endif

//-- Default Values used for resetting EEPROM -- 
        
//Default Peltier Current Limit (divide by 10 to avoid using float))
#define DEFAULT_CURRENT_LIMIT 40
    
//Default to Celsius
#define DEFAULT_TEMP_UNIT 'C'
        
//Default Temperature Limits
#define DEFAULT_MAX_INT_SETTING 70
#define DEFAULT_MAX_HOT_SETTINGS 80
    
//Demo mode is on by default
#define DEFAULT_DEMO_MODE true
    
//Default Plate Set Point
#define DEFAULT_LAST_TEMP_SETTING 10
    
//Default Temperature Hysteresis
//Will turn off at SET_POINT + OVER and on again at SET_POINT + UNDER
#define DEFAULT_TEMP_HYSTER_OVER 5
#define DEFAULT_TEMP_HYSTER_UNDER 5


#ifdef	__cplusplus
}
#endif

#endif	/* DEFAULTS_H */

