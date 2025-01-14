#include "runningMenus.h"
#include "peltierControl.h"

void runningMenus_runningSetup(void){     
    OLED_clear();
    if(settingMenus_getShowIcons()){
        //Show icons
        OLED_command(line_address[0]+11);
        OLED_data(0b00000101);
        OLED_data(0b00000110);
        OLED_writeString(":");

        OLED_command(line_address[0]);
        OLED_writeString("Set:");

        OLED_command(line_address[1]+1);
        OLED_data(0b00000001);
        OLED_data(0b00000010);
        OLED_writeString(":");


        OLED_command(line_address[1]+11);
        OLED_data(0b00000011);
        OLED_data(0b00000100);
        OLED_writeString(":");


    } else {
        // Show text
    OLED_command(line_address[0]+3);
    OLED_writeString("Plate:");
    
    OLED_command(line_address[1]);
    OLED_writeString("Heatsink:");

    OLED_command(line_address[2]+5);
    OLED_writeString("MCU:");
    }
    
    OLED_command(line_address[3]+6);
    OLED_writeString("Amps");
    OLED_command(line_address[3]+16);
    OLED_writeString("RPM");
    
    
}

void runningMenus_runningUpdate(int16_t moves){
    char disp_buff[20];
    if(settingMenus_getShowIcons()){
        // Show icons
        // update current Plate Temperature
        OLED_command(line_address[0]+14);
        sprintf(disp_buff, "%3d", dispTemp(Measurements_getLastColdTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        OLED_command(line_address[0]+4);
        sprintf(disp_buff, "%3d", dispTemp(settingMenus_getTargetTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        // MCU Temp
        OLED_command(line_address[1]+4);
        sprintf(disp_buff, "%3d", dispTemp(Measurements_getLastIntTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        OLED_command(line_address[1]+14);
        sprintf(disp_buff, "%3d", dispTemp(Measurements_getLastHotTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

    } else {
        // Show text
        
        // update current Plate Temperature
        OLED_command(line_address[0]+9);
        sprintf(disp_buff, "%3d/%3d", dispTemp(Measurements_getLastColdTemp()), dispTemp(settingMenus_getTargetTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        OLED_command(line_address[1]+12);
        sprintf(disp_buff, "%4d", dispTemp(Measurements_getLastHotTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        // MCU Temp
        OLED_command(line_address[2]+12);
        sprintf(disp_buff, "%4d", dispTemp(Measurements_getLastIntTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();
    }

    OLED_command(line_address[3]+1);
    sprintf(disp_buff, "%2d.%1d", (int)Measurements_getLastCurrent()/10, (int)Measurements_getLastCurrent()%10);
    OLED_writeString(disp_buff);
    
    OLED_command(line_address[3]+11);
    sprintf(disp_buff, "%4d", fanControl_getFan1RPM());
    OLED_writeString(disp_buff);
}


void runningMenus_errorSetup(void){
    OLED_clear();
    OLED_command(line_address[0]+2);
    OLED_writeString("Not Cool - Error");
    
    OLED_command(line_address[3]+3);
    OLED_writeString("Push to clear");
}

void runningMenus_errorUpdate(int16_t moves){
    OLED_command(line_address[2]);
    PeltierError currentError = peltierControl_getError();
    switch(currentError){
        case PELTIER_FAN1_ERROR:
            OLED_writeSpaces(1);
            OLED_writeString("Fan 1 Not Running");
            break;
        case PELTIER_HEATSINK_OVERHEAT:
            OLED_writeString("Heatsink Overheated");
            break;
        case PELTIER_INT_OVERHEAT:
            OLED_writeSpaces(3);
            OLED_writeString("MCU Overheated");
            break;
        case PELTIER_OVERCURRENT_ERROR:
            OLED_writeString("Overcurrent Error");
            break;
        case PELTIER_GAIN_ERROR:
            OLED_writeString("OPAMP Gain Error");
            break;
        case PELTIER_POWER_ERROR:
            OLED_writeSpaces(3);
            OLED_writeString("No Power Error");
            break;
        case PELTIER_PLATE_TEMP_LIMIT:
            OLED_writeSpaces(2);
            OLED_writeString("Peltier Too Cold");
            OLED_command(line_address[1]);
            OLED_writeString(" Safety Shutdown:");
            break;
        case PELTIER_SENSE_COLD_OPEN:
        case PELTIER_SENSE_HOT_OPEN:
            OLED_writeString("Check Connections");
            OLED_command(line_address[1]);
            OLED_writeSpaces(4);
            OLED_writeString("Temperature");
            
            OLED_command(line_address[0]);
            OLED_writeSpaces(1);
            if (currentError == PELTIER_SENSE_COLD_OPEN)
            {
                OLED_writeString("Invalid Cold Sense");            
            }
            else
            {
                OLED_writeString("Invalid Hot Sense");
            }

            break;
        case PELTIER_EEPROM_WRITE_FAIL:
            OLED_writeString("EEPROM Write Failure"); 
            break;
        case PELTIER_ERROR_NONE:
            break;
    }
    peltierControl_clearError(); // clear error after it has been displayed
}