#include "ThreadPool.h"



ThreadPool::ThreadPool()
{
	maxNumThreads = std::thread::hardware_concurrency();
}


ThreadPool::~ThreadPool()
{

}

void ThreadPool::SpawnWorkers()
{

	int numThreads;
	if (maxNumThreads > 5) 
	{
		numThreads = 5;
	}
	else 
	{
		numThreads = maxNumThreads;
	}

	if (threadingQueue.size() < numThreads)
	{
		//std::pair<Game *, int> astarPair = make_pair(this, i);
		//threadingQueue.push_back(SDL_CreateThread(&Game::runAstar, "WorkerThread:" + i, &astarPair));
	}
}

void ThreadPool::ConsumeJob()
{
}
