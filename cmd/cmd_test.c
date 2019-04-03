#include "commandConsole.h"

extern uint8_t versions_tab[];
static BaseType_t prvTestCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );


/* Structure that defines the "task" command line command. */
const CLI_Command_Definition_t xTest =
{
    "test", /* The command string to type. */
    "test:test <cmd> \r\n\
        'version' list the software vesion.\r\n\
        'reboot' reboot now.\r\n",
    prvTestCommand, /* The function to run. */
    1 
};




static BaseType_t prvTestCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
    
    const char *pcParameter;
    BaseType_t lParameterStringLength;

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    /* Obtain the parameter string. */
    pcParameter = FreeRTOS_CLIGetParameter  \
                    (
                        pcCommandString,        /* The command string itself. */
                        1,                        /* Return the first parameter. */
                        &lParameterStringLength    /* Store the parameter string length. */
                    );

    /* Sanity check something was returned. */
    configASSERT( pcParameter );


        
    if( strncmp( pcParameter, "version", strlen( "version" ) ) == 0 )
    {
        printf("%s\r\n",versions_tab);
    }
    else if( strncmp( pcParameter, "reboot", strlen( "reboot" ) ) == 0 )
    {
        printf("reboot now.\r\n");
        HAL_NVIC_SystemReset();
    }
    else
    {
        sprintf( pcWriteBuffer," '%s' Is Not a Valid parameters\r\n",pcParameter);
    }
        
    

    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;
    
}






