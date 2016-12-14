#pragma once
#include <vector>
#include "SDL_thread.h"
#include "SDL_timer.h"
#include <iostream>
#include <thread>

using namespace std;

class ThreadPool
{
private:
	int maxNumThreads;
	vector<SDL_Thread *> threadingQueue;
	SDL_mutex * mutex;
	int numberOfJobs;

public:
	ThreadPool();
	~ThreadPool();

	void SpawnWorkers();
	void ConsumeJob();

};

