#include "StdAfx.h"
#include "VirtualWifiTask.h"

void VirtualWifiTask::TASK_THREAD(LPVOID param)
{
	TASK_THREAD_PARAM *task_thrad_param=(TASK_THREAD_PARAM*)param;
	switch(task_thrad_param->task_type)
	{
		case TASK_TYPE_AUTO_START:
		{
            task_thrad_param->p_task->task_auto_start_init();
			break;
		}
		case TASK_TYPE_START_WIFI:
		{
			task_thrad_param->p_task->task_start_wifi();
			break;
		}
		case TASK_TYPE_CHECK_START:
		{
			task_thrad_param->p_task->task_check_start();
			break;
		}
		case TASK_TYPE_QUERY_STATUS:
		{
			task_thrad_param->p_task->task_query_status();
			break;
		}
		case TASK_TYPE_COUNT_FLOW:
		{
			 task_thrad_param->p_task->task_count_flow();
			 break;
		}
	}
	delete task_thrad_param;
}

