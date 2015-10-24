// Compile with:
// gcc TSP.c -lm -o TSP

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 10

struct point{
	float x;
	float y;
	int visited;
};

struct point pointset[N];

float dist(struct point p1, struct point p2){
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void print_coordinates(struct point * pointset){
	int i;
	for(i = 0; i < N; i++){
		printf("Point %i has coordinates : %f %f\n", i, pointset[i].x, pointset[i].y);
	}
}

void init_coordinates(struct point * pointset){
	int i;
	srand48(time(NULL));
	for(i = 0; i < N; i++){
		pointset[i].x = drand48();
		pointset[i].y = drand48();
	}
}

void zero_visited(struct point * pointset){
	int i;
	for(i = 0; i < N; i++){
		pointset[i].visited = 0;
	}
}

float TSP1(struct point * pointset){
	FILE * fout;
	fout = fopen("tour1.dat", "w");

	float tot_dist = 0;
	float p_dist;
	int num_visited = 0; 
	float min;
	int i;
	struct point p = pointset[0];
	pointset[0].visited = 1;
	struct point p1;
	int closest;

	fprintf(fout, "%f, %f\n", p.x, p.y);

	while (num_visited < N-1){
		min = 100000000;
		for(i = 0; i < N; i++){
			if (pointset[i].visited != 1){
				p_dist = dist(pointset[i], p);
				if(p_dist < min){
					min = p_dist;
					closest = i;
				}
			}
		}
		pointset[closest].visited = 1;
		p = pointset[closest];
		tot_dist = tot_dist + min;
		num_visited = num_visited + 1;
		fprintf(fout, "%f, %f\n", p.x, p.y);
	}
	fprintf(fout, "%f, %f\n", pointset[0].x, pointset[0].y);
	fclose(fout);
	tot_dist = tot_dist + dist(pointset[closest], pointset[0]);
	return tot_dist;
}

float TSP2(struct point pointset){
	float distance = 0;
	return distance;
}

int main(){
	init_coordinates(pointset);
	zero_visited(pointset);
	print_coordinates(pointset);
	printf("The distance given with the first heuristic is %f\n", TSP1(pointset));
	FILE * gnuplot = popen("gnuplot -persistent", "w");
	fprintf(gnuplot, "%s \n", "plot \"tour1.dat\" with lines");
}