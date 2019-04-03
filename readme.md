# cmd
一个裸机串口命令行模块

### 先来看一下效果： 
![use](https://github.com/redocCheng/cmd/edit/master/image/cmd_use )

### 命令文件构成： 
![cmd](https://github.com/redocCheng/cmd/edit/master/image/cmd_cmd)

### 移植注意点： 
    1、接收不定长串口数据，给命令行处理,demo中采用队列完成；
    2、命令行内部会发送，
    3、命令由链表管理，需要对其初始化

### 命令的格式： 
> cmd <param> <param> ... <param> (param的个数需要指定)

### 命令定义：  
```
const CLI_Command_Definition_t xTest =
{
    "test",                                 /* The command string to type. */
    "test:test <cmd> \r\n\     
        'version' list the software vesion.\r\n\
        'reboot' reboot now.\r\n",          /* The help of the cmd.        */
    prvTestCommand,                         /* The function to run.        */
    1                                       /* The num of param.           */
};
```

### 参数的使用： 
    解析相应的参数，以字符串相比较。例如解析第一个参数，该参数等于“version”，就输出当前软件的版本信息。使用的时候注意参数检测，非法参数做报错处理。
```
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
```

