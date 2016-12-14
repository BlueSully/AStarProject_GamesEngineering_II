#pragma once
#include <vector>
#include "SDL_thread.h"
#include "SDL_timer.h"
#include <iostream>
#include <thread>
#include <deque>
#include <utility>

using namespace std;

class ThreadPool
{
private:
	static ThreadPool * m_instance;

	int m_maxNumThreads;
	std::deque<std::pair<int, std::function<void()>>> m_job;//deck for Jobs
	vector<SDL_Thread *> m_threadingQueue;
	SDL_mutex * mutex;
	int m_numberOfJobs;

public:
	ThreadPool();
	~ThreadPool();

	static ThreadPool * getInstance();

	static int workerThread(void* ptr);
	void createWorkers();
	int getJobID() const;
	std::pair<int, std::function<void()>> doJob();
	void createJob(std::function<void()> func);

	bool jobFinished;
};


