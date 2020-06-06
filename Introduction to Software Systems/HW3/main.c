#include "list.h"
#include "set.h"
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINE_SIZE (256)

int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main() {
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* command;
	char* arg1;
	char* arg2;
	char* arg3;
	Bool res;
	int vertex1;
	int vertex2;
	int weight;
	int i;
	PGraph pGraph = NULL;
	PVertex pVertex = NULL;
	PEdge pEdge = NULL;

	//printf("%d\n", NULL);

	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
		command = strtok(szLine, delimiters);
		if(command == NULL)
		{
			continue;
		}
		if(strcmp(command,"create_graph") == 0)
		{
			pGraph = GraphCreate();
			if(pGraph == NULL)
			{
				fprintf(stderr, "create_graph execution failed.\n");
				continue;
			}
		}
		else if(strcmp(command,"add_vertex") == 0)
		{
			arg1 = strtok(NULL, delimiters);
			if(arg1 == NULL)
			{
				fprintf(stderr, "add_vertex failed: not enough parameters.\n");
				continue;
			}
			vertex1 = atoi(arg1);
			res = GraphAddVertex(pGraph,vertex1);
			if(res == FALSE)
			{
				fprintf(stderr, "add_vertex execution failed.\n");
				continue;
			}
		}
		else if(strcmp(command,"add_edge") == 0)
		{
			arg1 = strtok(NULL, delimiters);
			arg2 = strtok(NULL, delimiters);
			arg3 = strtok(NULL, delimiters);
			if(arg1 == NULL || arg2 == NULL || arg3 == NULL)
			{
				fprintf(stderr, "add_vertex failed: not enough parameters.\n");
				continue;
			}
			vertex1 = atoi(arg1);
			vertex2 = atoi(arg2);
			weight = atoi(arg3);
			res = GraphAddEdge(pGraph,vertex1,vertex2,weight);
			if(res == FALSE)
			{
				fprintf(stderr, "add_edge execution failed.\n");
				continue;
			}
		}
		else if(strcmp(command,"get_neighbors") == 0)
		{
			arg1 = strtok(NULL, delimiters);
			if(arg1 == NULL)
			{
				fprintf(stderr, "get_neighbors failed: not enough parameters.\n");
				continue;
			}
			vertex1 = atoi(arg1);
			PSet neighbors = GraphNeighborVertices(pGraph,vertex1);
			if(neighbors == NULL)
			{
				fprintf(stderr, "get_neighbors execution failed.\n");
				continue;
			}
			printf("The neighbors of vertex %d are:\n", vertex1);
			int size = SetGetSize(neighbors);
			if( size != 0 )
			{
				int* neighbors_serial = (int*)malloc(size*sizeof(int));
				if(neighbors_serial == NULL)
				{
					SetDestroy(neighbors);
					fprintf(stderr, "memory allocation failed.\n");
					continue;
				}
				pVertex = (PVertex)SetGetFirst(neighbors);
				int i = 0;
				while(pVertex)
				{
					neighbors_serial[i] = pVertex->serialNumber;
					pVertex = SetGetNext(neighbors);
					i++;
				}
				qsort (neighbors_serial, size, sizeof(*neighbors_serial), comp);
				for(i=0; i<size; i++)
				{
					printf("%d\n",neighbors_serial[i]);
				}
				free(neighbors_serial);
			}
			SetDestroy(neighbors);
		}
		else if(strcmp(command,"find_shortest_path") == 0)
		{
			arg1 = strtok(NULL, delimiters);
			if(arg1 == NULL)
			{
				fprintf(stderr, "find_shortest_path failed: not enough parameters.\n");
				continue;
			}
			vertex1 = atoi(arg1);
			int* dist = (int*)malloc(sizeof(int)*GraphGetNumberOfVertices(pGraph));
			if(dist == NULL)
			{
				fprintf(stderr, "find_shortest_path execution failed.\n");
				continue;
			}
			int* prev = (int*)malloc(sizeof(int)*GraphGetNumberOfVertices(pGraph));
			if(prev == NULL)
			{
				free(dist);
				fprintf(stderr, "find_shortest_path execution failed.\n");
				continue;
			}
			res = GraphFindShortestPath(pGraph,vertex1,dist,prev);
			if(res == FALSE)
			{
				free(dist);
				free(prev);
				fprintf(stderr, "find_shortest_path execution failed.\n");
				continue;
			}
			printf("Shortest Path Results:\n");
			for(i=0; i < GraphGetNumberOfVertices(pGraph); i++)
			{
				printf("The shortest path from source %-5d to %-5d costs: %-5d and the previous vertex is: %-5d\n", vertex1, i, dist[i],prev[i]);
			}

			free(dist);
			free(prev);
		} 
		else if(strcmp(command,"print_graph") == 0)
		{
			PSet vertices = GraphVerticesStatus(pGraph);
			if(vertices == NULL)
			{
				fprintf(stderr, "print_graph execution failed.\n");
				continue;
			}
			PSet edges = GraphEdgesStatus(pGraph);
			if(edges == NULL)
			{
				fprintf(stderr, "print_graph execution failed.\n");
				continue;
			}
			printf("Graph vertices:\n");
			pVertex = SetGetFirst(vertices);
			while(pVertex)
			{
				printf("%d\n",pVertex->serialNumber);
				pVertex = SetGetNext(vertices);
			}
			printf("Graph edges:\n");
			pEdge = SetGetFirst(edges);
			while(pEdge)
			{
				int nodeAnum = pEdge->nodeA->serialNumber;
				int nodeBnum = pEdge->nodeB->serialNumber;
				printf("%d-%d\n",nodeAnum < nodeBnum ? nodeAnum : nodeBnum ,nodeAnum >= nodeBnum ? nodeAnum : nodeBnum);
				pEdge = SetGetNext(edges);
			}
		}
		else if(strcmp(command,"exit") == 0)
		{
			break;
		}
		else
		{
			fprintf(stderr, "Command not found.\n");
		}
	}
	GraphDestroy(pGraph);
	return 0;
}

