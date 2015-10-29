// Compile with:
// gcc TSP.c -lm -o TSP

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 500

struct point{
	float x, y;
	int visited;
	struct point* neigh1;
	struct point* neigh2;
};

/*
Every point is an endpoint. If it gets two edges, it is not an end point.
If one or either of its prev and next pointers are null, it is an endpoint.
When we have an end point, we walk down its chain to see if the other vertex is in the chain - if not, it can be inserted.
*/
void connect_points(struct point* p1, struct point* p2){
	if(p1->neigh1 == NULL){p1->neigh1 = p2;}
	else{p1->neigh2 = p2;}
	if(p2->neigh1 == NULL){p2->neigh1 = p1;}
	else{p2->neigh2 = p1;}
}

int is_endpoint(struct point p){
	if((p.neigh1 == NULL)||(p.neigh2 == NULL)){return 1;}
	else {return 0;}
}

int in_chain(struct point* p1, struct point* p2){
	struct point * prev = malloc(sizeof(struct point));
	struct point * curr = malloc(sizeof(struct point));
	struct point * next = malloc(sizeof(struct point));
	curr = p1;
	int found = 0;
	if(p1->neigh1 == NULL){next = p1->neigh2;}
	else{next = p1->neigh1;}
	
	if(curr == p2){
		found = 1;
		return found;
	}	
	
	while(next != NULL){
		prev = curr;
		curr = next;
		next = (curr->neigh1 == prev) ? curr->neigh2 : curr->neigh1;
		if(curr == p2){
			found = 1;
			return found;
		}	
	}
	return found;
}

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
	// need to revise this, but I think it is correct.
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
		min = INFINITY;
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

float TSP2(struct point * pointset){
	FILE * fout;
	fout = fopen("tour2.dat", "w");

	float distance = 0.0;
	float d;
	int i, j, k, end_pt1, end_pt2;

	for(i = 0; i < N-1; i++){
		d = INFINITY;
		for(j = 0; j < N; j++){
			for(k = 0; k < N; k++){
				if((is_endpoint(pointset[j]) == 1)&&(is_endpoint(pointset[k]) == 1)&&
				   (in_chain(&pointset[j], &pointset[k]) == 0)&&(dist(pointset[k], pointset[j])<d)){
					d = dist(pointset[k], pointset[j]);
					end_pt1 = j; end_pt2 = k;
				}
			}
		}
		distance += d;
		connect_points(&pointset[end_pt1], &pointset[end_pt2]);
		fprintf(fout, "%f, %f\n", pointset[end_pt1].x, pointset[end_pt1].y);
		fprintf(fout, "%f, %f\n\n", pointset[end_pt2].x, pointset[end_pt2].y);
	}
	// find remaining end points
	end_pt1 = -1;
	end_pt2 = -1;
	for(i = 0; i < N; i++){
		if((is_endpoint(pointset[i]) == 1)&&(end_pt1 == -1)){
			end_pt1 = i;
		}
		if((is_endpoint(pointset[i]) == 1)&&(i != end_pt1)){
			end_pt2 = i;
			break;
		}
	}
	fprintf(fout, "%f, %f\n", pointset[end_pt1].x, pointset[end_pt1].y);
	fprintf(fout, "%f, %f\n\n", pointset[end_pt2].x, pointset[end_pt2].y);
	fclose(fout);
	return distance;
}

int main(){
	init_coordinates(pointset);
	zero_visited(pointset);
	print_coordinates(pointset);
	printf("The distance given with the first heuristic is %f\n" , TSP1(pointset));
	printf("The distance given with the second heuristic is %f\n", TSP2(pointset));
	FILE * gnuplot = popen("gnuplot -persistent", "w");
	fprintf(gnuplot, "%s \n", "plot \"tour1.dat\" with lines, \"tour2.dat\" with lines");

	FILE * gnuplot1 = popen("gnuplot -persistent", "w");
	fprintf(gnuplot1, "%s \n", "plot \"tour1.dat\" with lines");//, \"tour2.dat\" with lines");

	FILE * gnuplot2 = popen("gnuplot -persistent", "w");
	fprintf(gnuplot2, "%s \n", "plot \"tour2.dat\" with lines");
}