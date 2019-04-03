#include "commandConsole.h"
#include "includes.h"


static BaseType_t prvRebootCommand( char *RebootWriteBuffer, size_t xWriteBufferLen, const char *RebootCommandString );


/* Structure that defines the "Reboot" command line command. */
const CLI_Command_Definition_t xReboot =
{
    "reboot", /* The command string to type. */
    "reboot:\r\n  \
    reboot the cpu.\r\n",
    prvRebootCommand, /* The function to run. */
    0 /* No parameters are expected. */
};

        

static BaseType_t prvRebootCommand( char *RebootWriteBuffer, size_t xWriteBufferLen, const char *RebootCommandString )
{
    
    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) RebootCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( RebootWriteBuffer );

    printf("reboot now.\r\n");
    HAL_NVIC_SystemReset();
    
    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;
    
}





