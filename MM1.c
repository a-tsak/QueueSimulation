 /*
 ***********
 Anastasia Tsakalou
 2022201900226
 dit19226
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef double Item;

typedef struct node *link;	

struct node{
	Item data;
	Item data2;
	link next; 
};

typedef struct{
	link head, tail;
} QUEUE;	


void QUEUEput(QUEUE *q, Item item, Item item2);
Item QUEUEget(QUEUE *q);

int QUEUEempty(QUEUE *q);

void QUEUEinit(QUEUE *q);
void QUEUEfree(QUEUE *q);
void QUEUEprint(QUEUE *q);

double genrand(double rate);

void printTime(int time_h, int time_m, int time_s);		// Prints time in hours:minutes:seconds

Item QUEUEgetcomptime(QUEUE *q);						// Returns completion time of the first customer in queue
Item QUEUEgetarrtime(QUEUE *q);							// Returns arrival time of the first customer in queue

int main(){
	
	srand(time(NULL));
	
	QUEUE q;
	
	long i=0;							// Number of customers
	double l=0.5, m=1, rand1, rand2;			// l = Arrival rate, m = Service rate
	double sum1=0.0, avg, time=0.0;		// sum1 = Calculates total waiting time, avg = Average waiting time, time = Current time (minutes)
	Item time_arr=0, time_comp=0;		// Arrival time, Completion time (minutes)
	long count=0;
	Item t1,t2,diff;
	
	QUEUEinit(&q);						// Initialize queue
	
	while(i<500){								// Before 500 customers are reached (The queue can handle an infinite number of customers but the program should end)
		
		i++;									// 1 loop = 1 customer, customer++
		printf("\n\tClient %d\n",i);
		
		rand1 = genrand(l);						// Generate random time between arrivals
		time_arr = time_arr + rand1;			// Arrival time = arrival time + random time between arrivals
		
		time=time+time_arr;						// Current time is when the new customer just arrived

		double time_h = (double)time/60;		// Calculate minutes into hours, minutes, seconds to show time clearer
	    double time_m = fmod(time,60.0);
	    double time_s = time-(int) time;
	    time_s = time_s*60;
	    
		printf("Current time = %lf  ",time);	// Print the current time
		printTime(time_h,time_m,time_s);
		printf("\n");
		
		// Getting customers out of the queue
		
		while (!QUEUEempty(&q)){
			t1 = QUEUEgetcomptime(&q);
			if (time>=t1){					// If current time is bigger (after) than the first customer's completion time, get the first customer out of the queue
				Item e = QUEUEget(&q);		// Returns arrival time of the first customer in queue
			}
			else{							// Stop getting customers out of the queue when last customer's service isn't completed yet (current time < completion time)
				break;
			}
		}
		
		rand2 = genrand(m);				// Generate a random number between completions
		double duration = rand2;		// Duration = service time
		
		if (!QUEUEempty(&q)){
			time=0;
			time_comp = time_comp + duration;	// If the queue is not empty, completion time = completion time + duration
			// If the queue is not empty, the new customer will wait for the first customer till his completion time, plus his own service time
			
			// Calculating waiting time for the new customer
			t1 = QUEUEgetcomptime(&q);	// Getting first customer's completion time
			t2 = QUEUEgetarrtime(&q);	// Getting first customer's arrival time
			
			diff = t1-t2;
			sum1=sum1+diff;
			count++;
		}
		else{
			time=0;
			time_comp = time_arr + duration;	// If the queue is empty, completion time = arrival time + duration
		}
		
		QUEUEput(&q, time_arr, time_comp);		// Putting customer in queue
		
		QUEUEprint(&q);								// Print all the customers
		
		double time_ha = (double)time_arr/60;		// Calculate minutes of arrival time into hours, minutes, seconds
	    double time_ma = fmod(time_arr,60.0);
	    double time_sa = time_arr-(int) time_arr;
	    time_sa = time_sa*60;
	    
	    double time_hc = (double)time_comp/60;		// Calculate minutes of completion time into hours, minutes, seconds
	    double time_mc = fmod(time_comp,60.0);
	    double time_sc = time_comp-(int) time_comp;
	    time_sc = time_sc*60;
	    
		printf("Arrival = %.2lf\t", time_arr);
		printTime(time_ha, time_ma, time_sa);
		printf("\t | Duration = %.2lf\t", duration);
		printf("\t | Completion = %.2lf\t", time_comp);
		printTime(time_hc, time_mc, time_sc);
		printf("\n\n\n");
	}
	
	avg = sum1/count;				// Average waiting time in seconds
	printf("\nAverage waiting time = %.2lf\n\n", avg);
	QUEUEfree(&q);
	
}

void QUEUEinit(QUEUE *q){

	q->head = (link)malloc(sizeof(struct node)); 
	
	q->tail = q->head; 
	
	q->head->next = NULL;
}

void QUEUEfree(QUEUE *q){
	
	while(!QUEUEempty(q))
	
		QUEUEget(q);
		
	free(q->head);
}

int QUEUEempty(QUEUE *q){
	
	return q->head == q->tail;
}

void QUEUEput(QUEUE *q, Item item, Item item2){
	
	link t = (link)malloc(sizeof *t);
	
	t->data = item;
	
	t->data2 = item2;
	
	t->next = q->tail->next;
	
	q->tail->next = t;
	
	q->tail = t; 

}

Item QUEUEget(QUEUE *q){
	
	link t = q->head->next;
	
	Item u = q->head->next->data;
	q->head->next = t->next;
	
	if(q->tail == t)
		
		q->tail = q->head;
		
	free(t);
	
	return u;
	
}

Item QUEUEgetcomptime(QUEUE *q){
	
	Item u = q->head->next->data2;
	
	return u;				// Returning completion time of the first customer in queue
}

Item QUEUEgetarrtime(QUEUE *q){
	
	Item z = q->head->next->data;

	return z;				// Returning arrival time of the first customer in queue
}

void QUEUEprint(QUEUE *q){
	
	link z = q->head->next;
	int sum = 0;
	printf("Queue (arrival time, completion time): ");
	
	while(z != NULL){
			
		printf("(%.2lf , %.2lf), ",z->data,z->data2);
		
		z = z->next;
		sum++;
	}
	
	printf("\nCustomers in queue = %d\n", sum);
	
}

void printTime(int time_h, int time_m, int time_s){
	if (time_h<10){
		printf("[0%d",time_h);
	}
	else{
		printf("[%d",time_h);
	}
	if (time_m<10){
		printf(":0%d",time_m);
	}
	else{
		printf(":%d",time_m);
	}
	if (time_s<10){
		printf(":0%d]",time_s);
	}
	else{
		printf(":%d]",time_s);
	}
}

double genrand(double rate){
	
	int y;
	
	double p;
	
	while ((y = rand()) == RAND_MAX);
	
	p = (double) y / RAND_MAX;
	
	return -log(1-p) / rate;
	
}