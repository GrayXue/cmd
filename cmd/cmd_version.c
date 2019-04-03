#include "commandConsole.h"
#include "includes.h"

extern uint8_t versions_tab[];

static BaseType_t prvVersionCommand( char *versionWriteBuffer, size_t xWriteBufferLen, const char *versionCommandString );


/* Structure that defines the "version" command line command. */
const CLI_Command_Definition_t xVersion =
{
    "version", /* The command string to type. */
    "version:list the software vesion\r\n",
    prvVersionCommand, /* The function to run. */
    0 /* No parameters are expected. */
};

        

static BaseType_t prvVersionCommand( char *versionWriteBuffer, size_t xWriteBufferLen, const char *versionCommandString )
{
    
    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) versionCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( versionWriteBuffer );

    printf("%s\r\n",versions_tab);
    
    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;
    
}





