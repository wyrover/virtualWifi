#include "StdAfx.h"
#include "VirtualWifiTask.h"


VirtualWifiTask::VirtualWifiTask(void)
{
	
}

bool VirtualWifiTask::allocation_tasks(UINT u_task_id,WPARAM wParam/* =0 */,LPARAM lParam/* =0 */)
{
	BOOL b_is_post=PostThreadMessage(m_threadid,u_task_id,wParam,lParam);
	if (!b_is_post)
	{
		v_log->write_log("post message fail");
		return false;
	}
	return true;
}
bool VirtualWifiTask::allocation_tasks(TASK_TYPE task_type)
{
   TASK_THREAD_PARAM *task_thread_param=new TASK_THREAD_PARAM();
   task_thread_param->task_type=task_type;
   task_thread_param->p_task=this;
   _beginthread(TASK_THREAD,0,task_thread_param);
   return true;
}
void VirtualWifiTask::task_auto_start_init()
{
    
}
void VirtualWifiTask::set_thread_id(DWORD d_thread_id)
{
    m_threadid=d_thread_id;
}



VirtualWifiTask::~VirtualWifiTask(void)
{
}
