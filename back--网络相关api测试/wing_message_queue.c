/**
 *@��Ϣ����api
 */
#include "wing_message_queue.h"

//----��Ϣ����----------------------------
CRITICAL_SECTION queue_lock;


/**
 *@��ʼ����Ϣ����
 */
void message_queue_init( iocp_message_queue *&message_queue )  
{  
	InitializeCriticalSection(&queue_lock);
    message_queue->head = NULL; //��ͷ��־λ  
    message_queue->tail = NULL; //��β��־λ  
}  
   

/**
 *@����Ϣ����׷����Ϣ
 */
BOOL message_queue_lpush(iocp_message_queue *&message_queue , iocp_message_queue_element *element)  
{  
	if( message_queue == NULL || NULL == element)
		return 0;

	EnterCriticalSection(&queue_lock);

    iocp_message_queue_node *nnode = new iocp_message_queue_node();
	
    if (nnode == NULL )  
    {  
		LeaveCriticalSection(&queue_lock);
        return 0;
    } 

    nnode->data = element;  
    nnode->next = NULL;  
    if (message_queue->head == NULL)  
    {  
        message_queue->head = nnode;  
        message_queue->tail = nnode;  
    } else {  
        message_queue->tail->next = nnode;  
        message_queue->tail = nnode;  
    }  
	LeaveCriticalSection(&queue_lock);
    return 1;  
}  
  
/**
 *@������Ϣ
 */
void message_queue_pop(iocp_message_queue *&message_queue ,iocp_message_queue_element *&temp)  
{  
	if( NULL == message_queue ) 
	{
		temp = NULL;
		return;
	}

	EnterCriticalSection(&queue_lock);

    if ( message_queue->head == NULL )  
    {  
		temp = NULL;
		LeaveCriticalSection(&queue_lock);
		return;
    }  

	iocp_message_queue_node * p = NULL;  
    temp = message_queue->head->data;  
    p    = message_queue->head;  
    message_queue->head = message_queue->head->next;  
    if( message_queue->head == NULL )  
    {  
        message_queue->tail = NULL;  
    }  

    delete p;  
	p  = NULL;
	LeaveCriticalSection(&queue_lock);
}  
  
/**
 *@������Ϣ�ڵ� ������
 */
iocp_message_queue_element *peek_message_queue( iocp_message_queue *&message_queue )  
{  
	if( NULL == message_queue ) 
		return NULL;

    if ( message_queue->head == NULL)  
    {  
        return NULL; 
    }   
    return message_queue->head->data;  
}  
  
/**
 *@�ж϶����Ƿ�Ϊ��
 */
BOOL message_queue_isempty(iocp_message_queue *&message_queue)  
{  
	if( NULL == message_queue ) return 1;
    return message_queue->head == NULL;  
}  
 
/**
 *@��ն���
 */
void message_queue_clear(iocp_message_queue *&message_queue)  
{  
	if( NULL == message_queue ) return;

    iocp_message_queue_node *p = message_queue->head;  
    while(p != NULL)  
    {  
        message_queue->head = message_queue->head->next;  
        delete p; 
		p = NULL;
        p = message_queue->head;  
    }  
    message_queue->tail = NULL;  
	DeleteCriticalSection(&queue_lock);
	delete message_queue;
	message_queue = NULL;
    return;  
}  
//----��Ϣ����----------end------------------