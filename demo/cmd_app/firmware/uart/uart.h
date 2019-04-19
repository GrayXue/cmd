/**
  * @file        uart.h
  * @brief        ��������ͷ�ļ�
  * @author     redoc
  * @version    v1.0
  * @date        2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> (v1.0) 
  * ��ʼ�汾
  *
  * @remark
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "cqueue.h"

/**
  * @addtogroup SYSTEM����
  * @{
  */

/**
  * @addtogroup ��������
  * @{
  */



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/**
  * @defgroup ����������������
  * @{
  */




/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/**
  * @defgroup ���������ⲿ���ñ�������
  * @{
  */
extern queue_t queue_uart1_rx;

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @defgroup ���������ⲿ���ú�������
  * @{
  */
void uart_init(void);
void uart_queue_init(void);
void uart_rx_start(void);
uint8_t uart1_send(const uint8_t* buf,uint16_t len);
void uart_receive_process(void);
void uart_send_process(void);

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/  



/**
  * @}
  */  


/**
  * @}
  */  






#endif 

