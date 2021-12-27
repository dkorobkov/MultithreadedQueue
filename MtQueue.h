/*
 * MtQueue.h
 *
 *  Created on: Dec 24, 2021
 *      Author: user
 */

#ifndef MTQUEUE_H_
#define MTQUEUE_H_

#include <pthread.h>
#include <queue>

using namespace std;

class MtQueue {
public:
	MtQueue();
	virtual ~MtQueue();
	int size();
	void push_back(void* p);
	void* pop_front();
	void* front(); // Returns tail without removing item from queue

protected:
	std::queue<void*> qPtrs;
	void* pData;
	pthread_mutex_t mtx;
};

#endif /* MTQUEUE_H_ */
