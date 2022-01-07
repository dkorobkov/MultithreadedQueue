/*
 * MtQueue.cpp
 *
 *  Created on: Dec 24, 2021
 *      Author: user
 */

#include <stdio.h>
#include "MtQueue.h"

MtQueue::MtQueue()
{
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&mtx, NULL);
	entries = 0;
}

MtQueue::~MtQueue()
{
	pthread_mutex_destroy(&mtx);
}

int MtQueue::size()
{
	pthread_mutex_lock(&mtx);
	entries++;
	int ret = qPtrs.size();
	if(entries > 1)
		printf("ENTRIES>1!!!\n");
	entries--;
	pthread_mutex_unlock(&mtx);

	return ret;
}

void MtQueue::push_back(void* p)
{
	pthread_mutex_lock(&mtx);
	entries++;
	qPtrs.push(p);
	if(entries > 1)
		printf("ENTRIES>1!!!\n");
	entries--;
	pthread_mutex_unlock(&mtx);
}

void* MtQueue::pop_front() {
	pthread_mutex_lock(&mtx);
	entries++;
	void* ret = NULL;
	if(qPtrs.size() > 0)
	{
		ret = qPtrs.front();
		qPtrs.pop();
	}
	if(entries > 1)
		printf("ENTRIES>1!!!\n");
	entries--;
	pthread_mutex_unlock(&mtx);

	return ret;
}

void* MtQueue::front()
{
	pthread_mutex_lock(&mtx);
	entries++;
	void* ret = NULL;
	if(qPtrs.size() > 0)
		ret = qPtrs.front();
	if(entries > 1)
		printf("ENTRIES>1!!!\n");
	entries--;
	pthread_mutex_unlock(&mtx);

	return ret;
}
