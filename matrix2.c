#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h>

// compile like: gcc -Wall -O2 -DNROWS=10000 matrix2.c -o matrix2

#define NCOLS 100

void get_walltime(double *wct) {
	struct timeval tp; 
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() { 
	unsigned int a,b; 
	double *table,s,ts,te,t;


	table = (double *)malloc(NROWS*NCOLS*sizeof(double)); 
	if (table==NULL) {
		printf("alloc error!\n"); 
		exit(1);
	}

	// warmup
	for (a=0;a<NROWS*NCOLS;a++) {
		table[a] = 1.0;
	}

	// get starting time (double, seconds) 
	get_walltime(&ts);

	// workload 
	s = 0.0;
	for (b=0;b<NCOLS;b++) { 
		for (a=0;a<NROWS;a++) {
			s += table[a*NCOLS+b];
		}
	}
 
	// get ending time 
	get_walltime(&te);
	printf("sum = %f\n",s);

    // print time elapsed and/or Maccesses/sec
	t = ((double)NROWS*NCOLS)/((te-ts)*1e6);

	printf("avg array element Maccesses/sec = %f\n",t); 
	free(table);
	return 0;
}
