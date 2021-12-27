//============================================================================
// Name        : testMtQueue.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <pthread.h>
#include "MtQueue.h"
#include <unistd.h>

volatile bool bEnd = false;
volatile bool bTell1 = false;
volatile bool bTell2 = false;
volatile bool bTell3 = false;
volatile int delay = 100;


MtQueue q;

void* send(void* p)
{
	int nSent = 0;
	uint32_t elem;

	while(!bEnd)
	{
		if(q.size() > 10000)
			usleep(1000);

		void* p = new uint32_t[100000];
		uint32_t* u = (uint32_t*)p;
		u[0] = nSent;
		elem = nSent;
		q.push_back(p);

		nSent++;
		if(bTell1)
		{
			bTell1 = false;
			printf("Sent: %d (%d)\n", nSent, elem);
		}
	}

	printf("Sent: %d\n", nSent);

	return NULL;
}

void* receive(void* bt)
{
	int nRecv = 0;
	volatile bool* bTell = (volatile bool*)bt;

	int dly = delay;
	delay += 80; // diffferent delay in different threads

	printf("RECEIVE: %d\n", dly);

	while(!bEnd)
	{
		uint32_t elem;

		if(q.size() > 0)
		{
			void* p = q.pop_front();
			if(p != NULL)
			{
				uint32_t* u = (uint32_t*)p;
				elem = u[0];
				delete[] u;
				nRecv++;
			}
//			else printf("recv p=NULL (other thread grabbed it after call to size())\n");
		}
		else usleep(100);

		if(*bTell)
		{
			*bTell = false;
			printf("%cRecv: %d (%d)\n", dly == 100 ? '+' : '-', nRecv, elem);
		}
	}

	printf("%cRcvd: %d\n", dly == 100 ? '+' : '-', nRecv);

	return NULL;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	pthread_attr_t attr1, attr2, attr3;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr3);

	pthread_t thr1, thr2, thr3;
	pthread_create(&thr1, &attr1, &send, NULL);
	pthread_create(&thr2, &attr2, &receive, (void*)&bTell2);
	pthread_create(&thr3, &attr3, &receive, (void*)&bTell3);

	for(int i=0; i<1000; i++)
	{
		usleep(50000);
		bTell1 = bTell2 = bTell3 = true;
	}
	bEnd = true;
	usleep(200000);

	return 0;
}
