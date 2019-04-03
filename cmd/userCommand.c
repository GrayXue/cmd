/* FreeRTOS includes. */
#include "userCommand.h"
#include "commandConsole.h"
#include "includes.h"


/* FreeRTOS+CLI includes. */
static BaseType_t prvQuestionCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

extern const CLI_Command_Definition_t xQuestion;
extern const CLI_Command_Definition_t xReboot;
extern const CLI_Command_Definition_t xVersion;
extern const CLI_Command_Definition_t xTest;

CLI_Definition_List_Item_t list_xQuestion;
CLI_Definition_List_Item_t list_xReboot;
CLI_Definition_List_Item_t list_xVersion;
CLI_Definition_List_Item_t list_xTest;

/* Structure that defines the "?" command line command. */
const CLI_Command_Definition_t xQuestion =
{
    "?", /* The command string to type. */
    "?:? <cmd>\r\n  \
    get a command help\r\n",
    prvQuestionCommand, /* The function to run. */
    1 /* No parameters are expected. */
};


void user_command_init(void)
{
    command_console_init();
    
    /* Register all the command line commands defined immediately above. */
    //移植要点 命令初始化
    FreeRTOS_CLIRegisterCommand( &xQuestion , &list_xQuestion);
    FreeRTOS_CLIRegisterCommand( &xReboot , &list_xReboot);
    FreeRTOS_CLIRegisterCommand( &xVersion , &list_xVersion);
    FreeRTOS_CLIRegisterCommand( &xTest , &list_xTest);
}


static BaseType_t prvQuestionCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
    static const CLI_Definition_List_Item_t * pxCommand = NULL;
    BaseType_t xReturn;
    
    
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


    if( pxCommand == NULL )
    {
        /* Reset the pxCommand pointer back to the start of the list. */
        pxCommand = &xRegisteredCommands;
    }
    
    if(0 == strncmp(pcParameter,pxCommand->pxCommandLineDefinition->pcCommand ,strlen( pxCommand->pxCommandLineDefinition->pcCommand )))
    {
        strncpy( pcWriteBuffer,pxCommand->pxCommandLineDefinition->pcHelpString, xWriteBufferLen );
        
        xReturn = pdFALSE;
        
        pxCommand = NULL;
        
        return xReturn;
    }
    
    pxCommand = pxCommand->pxNext;
    
    if( pxCommand == NULL )
    {
        /* There are no more commands in the list, so there will be no more
        strings to return after this one and pdFALSE should be returned. */
        sprintf( pcWriteBuffer, " '%s' Is Not a Valid command \r\n",pcParameter);
        
        xReturn = pdFALSE;
    }
    else
    {
        xReturn = pdTRUE;
    }

    
    return xReturn;
}






