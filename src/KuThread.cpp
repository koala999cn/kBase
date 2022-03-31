#include "KuThread.h"
#include <thread>


void KuThread::sleep(float msec)
{
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(msec));
}