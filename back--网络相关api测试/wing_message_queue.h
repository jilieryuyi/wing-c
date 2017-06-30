#ifndef _MESSAGE_QUEUE_H
#define _MESSAGE_QUEUE_H
#include "Windows.h"

typedef struct _iocp_message_queue_element{
	int message_id;
	unsigned long lparam;
	unsigned long wparam;
	unsigned long eparam;

} iocp_message_queue_element;

typedef struct _iocp_message_queue_node   
{  
    iocp_message_queue_element *data;  
    struct _iocp_message_queue_node * next;  
} iocp_message_queue_node;            // �ڵ�Ľṹ  
  
typedef struct _iocp_message_queue  
{  
    iocp_message_queue_node * head;  
    iocp_message_queue_node * tail;  
} iocp_message_queue;          // ���еĽṹ  





/**
 *@��ʼ����Ϣ����
 */
void message_queue_init( iocp_message_queue* &message_queue ); 

/**
 *@����Ϣ����׷����Ϣ
 */
BOOL message_queue_lpush(iocp_message_queue *&message_queue , iocp_message_queue_element *element);  
  
/**
 *@������Ϣ
 */
void message_queue_pop(iocp_message_queue *&message_queue ,iocp_message_queue_element *&temp);  
  
/**
 *@������Ϣ�ڵ� ������
 */
iocp_message_queue_element *peek_message_queue( iocp_message_queue *&message_queue );  
  
/**
 *@�ж϶����Ƿ�Ϊ��
 */
BOOL message_queue_isempty(iocp_message_queue *&message_queue);
 
/**
 *@��ն���
 */
void message_queue_clear(iocp_message_queue *&message_queue);


#endif