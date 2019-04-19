/**
  * @file        uart.c
  * @brief        串口驱动
  * @author     redoc
  * @version    v1.0
  * @date        2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> (v1.0) 
  * 初始版本
  *
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "usart.h"
#include "shell.h"



 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

 
/* 队列定义 */ 
const uint16_t uart_bufnum_max = 512; 
uint8_t cqueue_uart1_rx_buf[uart_bufnum_max];
queue_t queue_uart1_rx;
uint8_t uart1_receive_buf[uart_bufnum_max];       

shellinput_t serial_shell;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void uart1_receive(void);
void uart_shell_unpack(void);

void uart_init(void)
{
    queue_init_static(&queue_uart1_rx,cqueue_uart1_rx_buf,uart_bufnum_max);
    shell_init("shell >",uart1_send);
    shell_input_init(&serial_shell,uart1_send);
}

uint8_t uart1_send(const uint8_t* buf,uint16_t len)
{
    if( !buf || len <1 )
    {
        return false;
    }
    
    HAL_UART_Transmit(&huart1,(uint8_t *)buf,len,0xffff);
    return true;
}

void uart_receive_process(void)
{ 
    uart1_receive();
    uart_shell_unpack();
}

static void uart1_receive(void)
{
    while(HAL_UART_Receive(&huart1,uart1_receive_buf, 100, 20) != HAL_TIMEOUT);

    uint16_t count = 99 - huart1.RxXferCount;
    if(count)
    {
        queue_put_length(&queue_uart1_rx,uart1_receive_buf,count);
    }
    
    huart1.RxXferCount = 99;
}


static void uart_shell_unpack(void)
{
    uint16_t len;
    uint8_t shell_rx_buf[256] = {0};
    
    len = queue_get_count(&queue_uart1_rx);
    
    if(len > 256)
    {
        len = 256;
    }

    
    queue_peek_length(&queue_uart1_rx,shell_rx_buf,len);
    queue_pop_length(&queue_uart1_rx,len);
    
    shell_input(&serial_shell,(char *)shell_rx_buf,len);
}





