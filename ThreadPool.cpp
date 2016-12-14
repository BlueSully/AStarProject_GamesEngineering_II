#include "ThreadPool.h"

ThreadPool * ThreadPool::m_instance = nullptr;

ThreadPool::ThreadPool()
{
	m_jobmutex = SDL_CreateMutex();
	sem = SDL_CreateSemaphore(0);
	m_maxNumThreads = std::thread::hardware_concurrency();
	m_numberOfJobs = 0;
}

ThreadPool::~ThreadPool()
{

}

ThreadPool * ThreadPool::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ThreadPool();
	}
	return m_instance;
}

int ThreadPool::workerThread(void * ptr)
{
	ThreadPool * thr_pool = ThreadPool::getInstance();
	int threadID = *(static_cast<int *>(ptr));
	while (true) 
	{
		SDL_SemWait(thr_pool->sem);
		auto job = thr_pool->doJob();//Get Job
		if (job.first >= 0) 
		{
			printf("Job: %d running on Thread: %d \n", job.first, threadID);
			job.second();
		}
	}
}

void ThreadPool::createWorkers()
{
	int numThreads;

	//if (m_maxNumThreads > 5)
	//{
	//	numThreads = 5;
	//}
	//else
	//{
		numThreads = m_maxNumThreads;
	//}

	if (static_cast<int>(m_threadingQueue.size()) < numThreads)
	{
		for (int i = 0; i < numThreads; i++)
		{
			int id = m_threadingQueue.size();
			m_threadingQueue.push_back(SDL_CreateThread(&ThreadPool::workerThread, "Worker:" + id, &id));
		}
	}
}

std::pair<int, std::function<void()>> ThreadPool::doJob()
{
	if (SDL_LockMutex(m_jobmutex) == 0)
	{
		if (m_job.empty())
			//if no jobs to work on give false job
		{
			SDL_UnlockMutex(m_jobmutex);
			return std::make_pair(-1, std::function<void()>());
		}

		std::pair<int, std::function<void()>> job;
		job = m_job.front();
		m_job.pop_front();
		SDL_UnlockMutex(m_jobmutex);
		return job;
	}
}

void ThreadPool::createJob(std::function<void()> func)
//Method for Adding a Function;
{
	SDL_LockMutex(m_jobmutex);
	int jobID = m_numberOfJobs;	
	m_job.push_back(std::make_pair(jobID, func));
	m_numberOfJobs++;
	SDL_SemPost(sem);
	SDL_UnlockMutex(m_jobmutex);
}