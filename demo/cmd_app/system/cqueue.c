/**
  * @file        cqueue.c
  * @brief        ���������ļ�
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
/* Includes ------------------------------------------------------------------*/
#include "cqueue.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
  * @addtogroup SYSTEM����
  * @{
  */

/**
  * @addtogroup ��������
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @defgroup ���������ⲿ��������
  * @{
  */
/**
  * @brief    ��ʼ������
  * @param    *QUEUE�����ж���
  * @param    *buffer�����������׵�ַ
  * @param    max_size����������
  *
  * @return    void    
  * @remark        
  */
void queue_init_static(queue_t *queue, uint8_t *buffer, uint16_t max_size) 
{
    queue->buffer = buffer;
    queue->max_size = max_size;
    queue->front = queue->rear = 0;
}

/**
  * @brief    ����������ݸ���
  * @param    *QUEUE�����ж���
  *
  * @return    uint8_t:�������ݸ���    
  * @remark        
  */
uint16_t  queue_get_count(queue_t *queue)
{
    if(queue->front < queue->rear)
        return queue->front + queue->max_size - queue->rear;
    else
        return queue->front - queue->rear;
}

/**
  * @brief    ��������
  * @param    *QUEUE�����ж���
  *
  * @return    uint8_t:������״̬
  * @remark        
  */
uint8_t queue_is_full(queue_t *queue)
{
    return (queue_get_count(queue)  == (queue->max_size - 1));
};

/**
  * @brief    �����п�
  * @param    *QUEUE�����ж���
  *
  * @return    uint8_t:���п�״̬
  * @remark        
  */
uint8_t queue_is_empty(queue_t *queue)
{
    return queue_get_count(queue) == 0;
};

/**
  * @brief    ��ȡ��������
  * @param    *QUEUE�����ж���
  *
  * @return    uint16_t:��������
  * @remark        
  */
uint16_t queue_get_size(queue_t *queue)
{    
    return queue->max_size;
};

/**
  * @brief    �����г�Ա�������
  * @param    *QUEUE�����ж���
  * @param    ch������
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
uint8_t queue_put(queue_t *queue,uint8_t ch)
{
      if(!queue_is_full(queue))
      {
        queue->buffer[queue->front]= ch;
        queue->front ++;
        queue->front %= queue->max_size; 
        return true;
      }
      else
        return false;
}

/**
  * @brief    ��ָ�����ȶ��г�Ա�������
  * @param    *QUEUE�����ж���
  * @param    *buffer�������׵�ַ
  * @param    length�����ݳ���
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
uint8_t queue_put_length(queue_t *queue,uint8_t *buffer,uint16_t length)
{
    int i;
    
    if(!((queue_get_size(queue)-queue_get_count(queue))<=length))
    {
        for (i = 0; i < length; ++i)
        {
            queue->buffer[queue->front]= *(buffer++);
            queue->front ++;
            queue->front %= queue->max_size; 
        }
        return true;
    }
    else
        return false;
}
/**
  * @brief    �����г�Աȡ������
  * @param    *QUEUE�����ж���
  * @param    ch������
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
uint8_t queue_get(queue_t *queue,uint8_t *ch)
{
      if (!queue_is_empty(queue))
      {
        *ch = queue->buffer[queue->rear];
        queue->rear++;
        queue->rear%=queue->max_size;   
        return true;
      }
      else
        return 0;
}

/**
  * @brief    ������ݣ����ǲ���������
  * @param    *QUEUE�����ж���
  * @param    ch������
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
uint8_t queue_peek(queue_t *queue,uint8_t *ch)
{
      if (!queue_is_empty(queue))
      {
        *ch = queue->buffer[queue->rear];
        return true;
      }
      else
        return false;
}

/**
  * @brief    ���ָ���������ݣ����ǲ���������
  * @param    *QUEUE�����ж���
  * @param    *buffer�������׵�ַ
  * @param    length�����ݳ���
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
uint8_t queue_peek_length(queue_t *queue,uint8_t *buffer,uint16_t length)
{
    int i;
    uint8_t     rt = false;
    for (i = 0; i < length; ++i)
    {
        *(buffer++) = queue->buffer[(queue->rear + i) % queue->max_size];
        rt = true;
    }

    return rt;
}

/**
  * @brief    ����������ݣ����ǲ���������
  * @param    *QUEUE�����ж���
  * @param    *buffer�������׵�ַ
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
uint8_t queue_peek_all(queue_t *queue,uint8_t *buffer)
{
    int back_tail;
    uint8_t     rt = false;
    if( !buffer ) return false;

    back_tail = queue->rear;
    
    while (back_tail != queue->front)
    {
        *(buffer++) = queue->buffer[back_tail];
        ++back_tail;
        back_tail %= queue->max_size;
        rt = true;
    }

    return rt;
}

/**
  * @brief    POPһ�����ݣ���ʹ������
  * @param    *QUEUE�����ж���
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
void queue_pop(queue_t *queue)
{
      if (!queue_is_empty(queue))
      {
        queue->rear++;
        queue->rear%=queue->max_size;   
      }
}

/**
  * @brief    POPָ���������ݣ���ʹ������
  * @param    *QUEUE�����ж���
  * @param    pos������
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
void queue_pop_length(queue_t *queue,uint16_t length)
{
      if (!queue_is_empty(queue))
      {
        queue->rear+=length;
        queue->rear%=queue->max_size;   
      }
}

/**
  * @brief    POP�������ݣ���ʹ������
  * @param    *QUEUE�����ж���
  *
  * @return    uint8_t:����״̬
  * @remark        
  */
void queue_pop_all(queue_t *queue)
{
    queue->front = 0;
    queue->rear = 0;
}
  
/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */




