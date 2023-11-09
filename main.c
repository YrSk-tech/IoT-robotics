#include <project.h>
#include <stdbool.h>
#include <string.h>

#define NMEA_MAX_LENGTH 100

int main() {
    char neo_data;
    char nmea_sentence[NMEA_MAX_LENGTH];
    uint8 nmea_index = 0;
    bool sentence_start = false;
    char *latitude = NULL;
    char *longitude = NULL;
    char *ns_indicator = NULL;
    char *ew_indicator = NULL;
    int fieldIndex = 0;

    UART_Init();
    LCD_Init();

    UART_Start();
    LCD_Start();
    
    memset(nmea_sentence, '\0', NMEA_MAX_LENGTH); 

    for (;;) {
        neo_data = UART_UartGetChar(); 

        if (neo_data != 0) { 
            if (neo_data == '$') { 
                sentence_start = true;
                nmea_index = 0;
                fieldIndex = 0;
                latitude = NULL;
                longitude = NULL;
                ns_indicator = NULL;
                ew_indicator = NULL;
            }

            if (sentence_start) {
                nmea_sentence[nmea_index++] = neo_data;

                if (neo_data == '\n' || nmea_index == NMEA_MAX_LENGTH - 1) { // Check for end of NMEA sentence or buffer overflow
                    sentence_start = false;
                    nmea_sentence[nmea_index] = '\0'; // Null-terminate the string
                    
                    // Parse the NMEA sentence
                    char *token = strtok(nmea_sentence, ",");

                    
                    while (token != NULL) {
                        fieldIndex++;
                        if (fieldIndex == 4) { 
                            latitude = token;
                        } else if (fieldIndex == 5) { 
                            ns_indicator = token;
                        } else if (fieldIndex == 6) { 
                            longitude = token;
                        } else if (fieldIndex == 7) { 
                            ew_indicator = token;
                            // We have both latitude and longitude, can display them
                            if (latitude && longitude && ns_indicator && ew_indicator) {
                                LCD_ClearDisplay();
                                LCD_Position(0, 0);
                                LCD_PrintString("Lat:");
                                LCD_PrintString(latitude);
                                LCD_PrintString(ns_indicator);
                                LCD_Position(1, 0);
                                LCD_PrintString("Lon:");
                                LCD_PrintString(longitude);
                                LCD_PrintString(ew_indicator);
                                CyDelay(500);
                                break; // Exit the loop as we have displayed the data
                            }
                        }
                        token = strtok(NULL, ","); // Move to the next token
                    }
                    
                    memset(nmea_sentence, '\0', NMEA_MAX_LENGTH); // Clear the buffer for the next sentence
                    nmea_index = 0; // Reset index
                }
            }
        }
    }
}
