#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#include "../sharedFile/shared.h"




/*===================================================
 * Plane manager:
 * N runway, P planes (P > N).   The planes are landing in a FIFO order.
 * Synchronization method: mutex lock to synchronize the access to a waiting queue + condition variable
 * Parameters (non mandatory): <number of planes > 0> <number of runways > 0>
 ====================================================*/




char				*busyRunway;					// Indicates whether a runway is busy or not
waitingQueue		*queue;							// Waiting queue of the plains which want to land
pthread_mutex_t		lock;							// Allows at most 1 thread to access the runway state
int					nbrRunway;




void *land(void *arg)								// Function executed by each thread (plane)
{
	int	planeID	= (int) arg, threadIDInQueue;
	int freeRunway;

	pthread_mutex_lock(&lock);						// Add the thread id in the waiting queue (critical section)
	printf("Plane %d tries to land\n", planeID);
	threadIDInQueue = appendToQueue(queue);

	while(!isTurn(queue, threadIDInQueue))			// Wait for my name to be on the top of the waiting queue
	{
		pthread_cond_wait(&(queue->condVar), &lock);
	}
	freeRunway = getFreeRunway(busyRunway, nbrRunway);
	busyRunway[freeRunway] = 1;
	printf("\t\t\t- Runway %d: plane %d start landing\n", freeRunway, planeID);
	pthread_mutex_unlock(&lock);

	usleep(400);
	printf("\t\t\t\t\t\t\t\t- Runway %d: plane %d ends landing\n", freeRunway, planeID);

	pthread_mutex_lock(&lock);						// Remove the thread id from the waiting queue (critical section)
	leaveQueue(queue);
	busyRunway[freeRunway] = 0;
	pthread_cond_broadcast(&(queue->condVar));
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(int argc, char **argv)
{
	int nbrPlanes, i;

	if (argc > 1)									// Initialize the number of planes
	{
		nbrPlanes = atoi(argv[1]);
		if (nbrPlanes <= 0) nbrPlanes = NBR_PLANES;
	}
	else nbrPlanes = NBR_PLANES;
	if (argc > 2)									// Initialize the number of runways
	{
		nbrRunway = atoi(argv[2]);
		if (nbrRunway <= 0) nbrRunway = NBR_RUNWAY;
	}
	else nbrRunway = NBR_RUNWAY;
	busyRunway = malloc(nbrRunway * sizeof(char));
	for (i=0; i<nbrRunway; i++)	busyRunway[i] = 0;

	pthread_t tids[nbrPlanes];						// Initialize the thread id struct
	pthread_mutex_init(&lock, NULL);				// Initialize the lock
	queue = newWaitingQueue(nbrRunway);				// Initialize the waiting queue

	for (i=0; i<nbrPlanes; i++)						// Run the concurrent threads
		pthread_create (&tids[i], NULL, land, (void*)i);
	for (i=0; i<nbrPlanes; i++)						// Wait for all the threads to finish
		pthread_join(tids[i], NULL);

	free(busyRunway);
	pthread_mutex_destroy(&lock);
	destroyWaitingQueue(queue);
	return 0;
}
