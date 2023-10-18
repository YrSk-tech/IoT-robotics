
#include <project.h>
int main()
{
    char neo_data;
    UART_Init();
    LCD_Init();
    
    /* Start SCB (UART mode) operation */
    UART_Start();
    LCD_Start();
    for (;;)
    {
        neo_data = UART_UartGetChar();
        /* Get received character or zero if nothing has been received yet */
        LCD_Position(0, 0); // Set the cursor to the first line, first character.
        LCD_PrintString("Neo 6m GPS data");
        if (neo_data != UART_UartGetChar()) // Check if any data is received.
        {
                LCD_Position(1, 0);
                LCD_PrintString(&neo_data);
            
        }
        CyDelay(100);
    }
}


