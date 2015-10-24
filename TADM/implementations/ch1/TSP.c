#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 10

struct point{
	double x;
	double y;
	int visited;
};

struct point pointset[N];

double dist(struct point p){
	return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

void init_coordinates(struct point * pointset){
	int i;
	for(i = 0; i < N; i++){
		pointset[i].x = rand();
		pointset[i].y = rand();
	}
}

void zero_visited(struct point * pointset){
	int i;
	for(i = 0; i < N; i++){
		pointset[i].visited = 0;
	}
}

int main(){
	init_coordinates(pointset);
	zero_visited(pointset);
	int i; 
	for(i = 0; i < N; i++){
		printf("Point %d has x abscissa: %f", i, pointset[i].x);
	}
}