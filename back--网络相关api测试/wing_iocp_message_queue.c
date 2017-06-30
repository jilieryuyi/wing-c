
/***
 *@iocp��Ϣ���з�װ
 */

#include "wing_message_queue.h"

iocp_message_queue *_iocp_message_queue = NULL;// new iocp_message_queue();

/***
 *@iocp��Ϣ���г�ʼ��
 */
void iocp_message_queue_init(){
	_iocp_message_queue = new iocp_message_queue();
	message_queue_init(_iocp_message_queue);
}

/**
 * @ post ������Ϣ
 */
void iocp_post_queue_msg( int message_id, unsigned long wparam, unsigned long lparam, unsigned long eparam )
{
		
	iocp_message_queue_element *msg	= new iocp_message_queue_element();  

	msg->message_id = message_id;                          //��Ϣid
	msg->wparam		= wparam;                              //����1
	msg->lparam		= lparam;	                           //����2
	msg->eparam		= eparam;                              //��չ���� 3

	message_queue_lpush(_iocp_message_queue,msg);	
}

/**
 *@pop��Ϣ���� û����Ϣʱ�Զ������߳�
 */
void iocp_message_queue_get( iocp_message_queue_element *&msg )
{
	while( message_queue_isempty( _iocp_message_queue ) )
	{
		Sleep(10);
	}
	message_queue_pop(_iocp_message_queue , msg);
}

void iocp_message_queue_clear(){
	message_queue_clear(_iocp_message_queue);
}
 