#include "ThreadPool.h"

ThreadPool * ThreadPool::m_instance = nullptr;

ThreadPool::ThreadPool()
{
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
		auto job = thr_pool->doJob();//Get Job
		if (!(job.first < 0)) 
		{
			printf("Job: %d running on Thread: %d \n", job.first, threadID);
			job.second();
		}
	}
}

void ThreadPool::createWorkers()
{
	int numThreads;

	if (m_maxNumThreads > 5)
	{
		numThreads = 5;
	}
	else
	{
		numThreads = m_maxNumThreads;
	}

	numThreads = 2;

	if (static_cast<int>(m_threadingQueue.size()) < numThreads)
	{
		for (int i = 0; i < numThreads; i++)
		{
			int id = m_threadingQueue.size();
			m_threadingQueue.push_back(SDL_CreateThread(&ThreadPool::workerThread, "Worker:" + id, &id));
		}
	}
}

int ThreadPool::getJobID() const
{
	return 0;
}

std::pair<int, std::function<void()>> ThreadPool::doJob()
{
	std::pair<int, std::function<void()>> job;
	if (m_job.empty()) 
	//if no jobs to work on give false job
	{
		return std::make_pair(-1, std::function<void()>());
	}
	else if (!m_job.empty())
	{
		job = m_job.front();
		m_job.pop_front();
		return job;
	}
}

void ThreadPool::createJob(std::function<void()> func)
//Method for Adding a Function;
{
	int jobID = m_numberOfJobs;
	//NEED TO LOCK THIS
	m_job.push_back(std::make_pair(jobID, func));
	m_numberOfJobs++;
}