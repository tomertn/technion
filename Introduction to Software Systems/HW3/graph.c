#include "graph.h"
#include <limits.h>


//*********************************************************************************
//* function name: createVertex
//* Description  : Create a new vertex, and return NULL for failure.
//* Parameters   : serial - the serial no. of the new vertex.
//* Return value : PVertex - pointer to the new vertex.
//*********************************************************************************
PVertex createVertex(int serial) {
	PVertex pVertex = (PVertex)malloc(sizeof(Vertex));
	if (pVertex == NULL) return NULL;
	pVertex->serialNumber = serial;
	return pVertex;
}


//*********************************************************************************
//* function name: destroyVertex
//* Description  :destroy a vertex. 
//* Parameters   : PElem - a pointer to the vertex.
//* Return value : -
//*********************************************************************************
void destroyVertex(PElem pElem) {
	if (pElem == NULL) return;
	PVertex pVertex = (PVertex)pElem;
	free(pVertex); return;
}

//*********************************************************************************
//* function name: vertexClone
//* Description  : copy given vertex. return NULL for FAILURE 
//* Parameters   : PElem - a pointer to the vertex.
//* Return value : PElem - the pointer for the copy of the vertex.
//*********************************************************************************
PElem vertexClone(PElem pElem) {
	if (pElem == NULL) return NULL;
	PVertex pVertex = (PVertex)pElem;
	PElem pVCpy = createVertex(pVertex->serialNumber);
	return pVCpy;
}

//*********************************************************************************
//* function name: cmpVertex
//* Description  :compare between 2 verteces. 
//* Parameters   : PElem - a pointer to a vertex.
//				   PElem - a pointer to a vertex.
//* Return value : TRUE/FALSE for equal/not equal.
//*********************************************************************************
Bool cmpVertex(PElem pElem1, PElem pElem2) {
	PVertex ver1 = (PVertex)pElem1;
	PVertex ver2 = (PVertex)pElem2; 
	if (ver1->serialNumber == ver2->serialNumber) return TRUE;
	return FALSE;
}
/*
void destroyVertex(PVertex pVertex) {
	if (pVertex == NULL) return;
	free(pVertex); return;
}

PVertex vertexClone(PVertex pVertex) {
	if (pVertex == NULL) return NULL;
	PVertex pVCpy = createVertex(pVertex->serialNumber);
	return pVCpy;
}

Bool cmpVertex(PVertex ver1, PVertex ver2) {
	if (ver1->serialNumber == ver2->serialNumber) return TRUE;
	return FALSE;
}
*/

//*********************************************************************************
//* function name: createEdge
//* Description  : Create a new edge, and return NULL for failure.
//* Parameters   : int - nodeA : the serial for the 1st vertex.
//				   int - nodeB : the serial for the 2nd vertex.
//				   int - weight : the weight of the edge.
//* Return value : PEdge - pointer to the new edge.
//*********************************************************************************

PEdge createEdge(int nodeA, int nodeB, int weight) {
	PEdge pEdge = (PEdge)malloc(sizeof(struct _Edge));
	if (pEdge == NULL) return NULL;
	if (nodeA == nodeB || nodeA < 0 || nodeB < 0 || weight > 10 || weight < 0)
	{ free(pEdge); return NULL; }
	pEdge->nodeA = createVertex(nodeA);
	if (pEdge->nodeA == NULL) { free(pEdge); return NULL; }
	pEdge->nodeB = createVertex(nodeB);
	if (pEdge->nodeB == NULL) {destroyVertex(pEdge->nodeA); free(pEdge); return NULL; }
	pEdge->weight = weight;
	return pEdge;
}
/*
void destroyEdge(PEdge pEdge) {
	if (pEdge == NULL) return;
	destroyVertex(pEdge->nodeA);
	destroyVertex(pEdge->nodeB);
	free(pEdge); return;
}

PEdge edgeClone(PEdge pEdge) {
	if (pEdge == NULL) return NULL;
	PEdge pECpy = createEdge(pEdge->nodeA->serialNumber,pEdge->nodeB->serialNumber,pEdge->weight);
	return pECpy;
}

Bool cmpEdge(PEdge edge1, PEdge edge2) {
	if (cmpVertex(edge1->nodeA,edge2->nodeA) 
		&& cmpVertex(edge1->nodeB, edge2->nodeB)) return TRUE;
	if (cmpVertex(edge1->nodeA, edge2->nodeB) 
		&& cmpVertex(edge1->nodeB, edge2->nodeA)) return TRUE;
	return FALSE;
}
*/

//*********************************************************************************
//* function name: destroyEdge
//* Description  :destroy a edge. 
//* Parameters   : PElem - a pointer to the edge.
//* Return value : -
//*********************************************************************************
void destroyEdge(PElem pElem) {
	PEdge pEdge = (PEdge)pElem;
	if (pEdge == NULL) return;
	destroyVertex(pEdge->nodeA);
	destroyVertex(pEdge->nodeB);
	free(pEdge); return;
}

//*********************************************************************************
//* function name: edgeClone
//* Description  : copy a given edge. return NULL for FAILURE 
//* Parameters   : PElem - a pointer to the edge.
//* Return value : PElem - the pointer for the copy of the edge.
//*********************************************************************************

PElem edgeClone(PElem pElem) {
	PEdge pEdge = (PEdge)pElem;
	if (pEdge == NULL) return NULL;
	PEdge pECpy = createEdge(pEdge->nodeA->serialNumber, pEdge->nodeB->serialNumber, pEdge->weight);
	return pECpy;
}

//*********************************************************************************
//* function name: cmpEdge
//* Description  :compare between 2 edges. 
//* Parameters   : PElem - a pointer to an edge.
//				   PElem - a pointer to an edge.
//* Return value : TRUE/FALSE for equal/not equal.
//*********************************************************************************

Bool cmpEdge(PElem pElem1, PElem pElem2) {
	PEdge edge1 = (PEdge)pElem1;
	PEdge edge2 = (PEdge)pElem2;
	if (cmpVertex(edge1->nodeA, edge2->nodeA)
		&& cmpVertex(edge1->nodeB, edge2->nodeB)) return TRUE;
	if (cmpVertex(edge1->nodeA, edge2->nodeB)
		&& cmpVertex(edge1->nodeB, edge2->nodeA)) return TRUE;
	return FALSE;
}

struct _Graph {
	PSet vertexSet;
	PSet edgeSet;
	int vertexNum;
};

//*********************************************************************************
//* function name: GraphCreate
//* Description  : Create a new Graph, and return NULL for failure.
//* Parameters   : -
//* Return value : PGraph - pointer to the new graph.
//*********************************************************************************
PGraph GraphCreate() {
	PGraph pGraph = (PGraph)malloc(sizeof(struct _Graph));
	if (pGraph == NULL) return NULL;
	pGraph->vertexSet = SetCreate(cmpVertex,vertexClone,destroyVertex); 
	if (pGraph->vertexSet == NULL) { free(pGraph);  return NULL; }
	pGraph->edgeSet = SetCreate(cmpEdge,edgeClone,destroyEdge); 
	if (pGraph->edgeSet == NULL) { SetDestroy(pGraph->vertexSet); free(pGraph);  return NULL; }
	pGraph->vertexNum = 0;
	return pGraph;
}

//*********************************************************************************
//* function name: GraphDestroy
//* Description  :destroy the graph. 
//* Parameters   : PGraph - a pointer to the graph.
//* Return value : -
//*********************************************************************************
void GraphDestroy(PGraph pGraph) {
	if (pGraph == NULL) return;
	SetDestroy(pGraph->edgeSet);
	SetDestroy(pGraph->vertexSet);
	free(pGraph);
}

//*********************************************************************************
//* function name: GraphAddVertex
//* Description  : Add a new vertex to a graph. 
//* Parameters   : PGraph - a pointer to a Graph.
//				   int - the place for inserting.
//* Return value : TRUE/FALSE for success or failure.
//*********************************************************************************
Bool GraphAddVertex(PGraph pGraph, int n) {
	if (pGraph == NULL) return FALSE;
	if (n != pGraph->vertexNum) return FALSE;
	PVertex pVertex = createVertex(n);
	if (pVertex == NULL) return FALSE;
	if (!SetAdd(pGraph->vertexSet, pVertex)) return FALSE;
	(pGraph->vertexNum)++;
	free(pVertex);
	return TRUE;
}

//*********************************************************************************
//* function name: GraphAddEdge
//* Description  : Add a new edge to a graph. 
//* Parameters   : PGraph - a pointer to a Graph.
//				   int vertex1- the serial of 1st vertex.
//				   int vertex2- the serial of 2nd vertex.
//				   int weight- the weight of the edge.
//* Return value : TRUE/FALSE for success or failure.
//*********************************************************************************

Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight) {

	if (pGraph == NULL || vertex1 > pGraph->vertexNum || vertex2 > pGraph->vertexNum 
		|| vertex1 < 0 || vertex2 < 0 || vertex1 == vertex2 || weight > 10 || weight < 0) 
		return FALSE;
	
	PEdge pEdge = createEdge(vertex1, vertex2, weight);

	if (pEdge == NULL) 
		return FALSE;
	if (SetAdd(pGraph->edgeSet, pEdge) == FALSE)
		{destroyEdge(pEdge); return FALSE; }

	destroyEdge(pEdge); 
	return TRUE;
}

//*********************************************************************************
//* function name: GraphNeighborVertices
//* Description  : find and return a set of neighbors of a specific vertex. 
//* Parameters   : PGraph - a pointer to a Graph.
//				   int vNum- the serial/place of a given vertex.
//* Return value : PSet - pointer to the set of neighbors; NULL for failure.
//*********************************************************************************

PSet GraphNeighborVertices(PGraph pGraph, int vNum) {
	if (pGraph == NULL || vNum >= pGraph->vertexNum || vNum < 0 
		|| pGraph->edgeSet == NULL ) return NULL;
	PEdge ipEdge = SetGetFirst(pGraph->edgeSet);
	if (ipEdge == NULL) return NULL;
	PSet vSet = SetCreate(cmpVertex, vertexClone, destroyVertex);
	if (vSet == NULL) return NULL;
	while (ipEdge) {
		if (ipEdge->nodeA->serialNumber == vNum && ipEdge->nodeB->serialNumber != vNum)
			SetAdd(vSet, ipEdge->nodeB);
		else if (ipEdge->nodeB->serialNumber == vNum && ipEdge->nodeA->serialNumber != vNum)
			SetAdd(vSet, ipEdge->nodeA);
		ipEdge = SetGetNext(pGraph->edgeSet);
	}
	return vSet;
}

//*********************************************************************************
//* function name: GraphGetNumberOfEdges
//* Description  : return the number of edges in a given graph. 
//* Parameters   : PGraph - a pointer to a Graph.
//* Return value : int - the number of edges. return 0 for no edges or failure.
//*********************************************************************************

int GraphGetNumberOfEdges(PGraph pGraph) {
	if (pGraph == NULL) return 0;
	return SetGetSize(pGraph->edgeSet);
}

//*********************************************************************************
//* function name: GraphGetNumberOfVertices
//* Description  : return the number of vertices in a given graph. 
//* Parameters   : PGraph - a pointer to a Graph.
//* Return value : int - the number of vertices. return 0 for no vertices or failure.
//*********************************************************************************

int GraphGetNumberOfVertices(PGraph pGraph) {
	if(pGraph == NULL) return 0;
	return SetGetSize(pGraph->vertexSet); // or return pGraph->vertexNum
}

//*********************************************************************************
//* function name: GraphVerticesStatus
//* Description  : return the Set of vertices in a given graph. 
//* Parameters   : PGraph - a pointer to a Graph.
//* Return value : PSet - pointer to the set of vertices. return NULL for failure.
//*********************************************************************************

PSet GraphVerticesStatus(PGraph pGraph) {
	if (pGraph == NULL) return NULL;
	return pGraph->vertexSet;
}

//*********************************************************************************
//* function name: GraphEdgesStatus
//* Description  : return the Set of edges in a given graph. 
//* Parameters   : PGraph - a pointer to a Graph.
//* Return value : PSet - pointer to the set of edges. return NULL for failure.
//*********************************************************************************

PSet GraphEdgesStatus(PGraph pGraph) {
	if (pGraph == NULL) return NULL;
	return pGraph->edgeSet;
}


//*********************************************************************************
//* function name: findWeight
//* Description  : finding the edge weight that connect two given vertic in given graph
//* Parameters   : pGraph- a pointer to the graph
//                 aVertex- a pointer to the first vertex 
//                 bVertex- a pointer to the secend vertex 
//* Return value : int, the edge weight, -1 for fail
//*********************************************************************************
int findWeight(PGraph pGraph, PVertex aVertex, PVertex bVertex) {
	PEdge thisEdge = SetGetFirst(pGraph->edgeSet);
	if (aVertex == NULL || bVertex == NULL || pGraph == NULL) { return -1; }//checking the inputs
	if (aVertex->serialNumber == bVertex->serialNumber) { return 0; }
	while (thisEdge != NULL) {
		if ((thisEdge->nodeA->serialNumber == aVertex->serialNumber) && (thisEdge->nodeB->serialNumber == bVertex->serialNumber)) {
			return thisEdge->weight;
		}
		if ((thisEdge->nodeB->serialNumber == aVertex->serialNumber) && (thisEdge->nodeA->serialNumber == bVertex->serialNumber)) {
			return thisEdge->weight;
		}
		thisEdge = SetGetNext(pGraph->edgeSet);
	}
	return -1;
}

//*********************************************************************************
//* function name: GraphFindShortestPath
//* Description  : finding the shortes path frome given source vertic to any other 
//                 vertic in given graph. save the path value and the previes vertic
//                 to given arrys.
//* Parameters   : pGraph- a pointer to the graph
//                 source- intenger of the source serial number
//                 dist- a pointer to distence arry
//                 prev- a pointer to previes vertic arry
//* Return value : Bool, TRUE for run success or FALSE for run failure
//*********************************************************************************
Bool GraphFindShortestPath(PGraph pGraph, int source, int* dist, int* prev) {
	if (pGraph == NULL) { return FALSE; }
	if((source> GraphGetNumberOfVertices(pGraph)-1)||(source<0)){ return FALSE; }
	if (GraphGetNumberOfVertices(pGraph) == 1) {// in case there is only one vertic
		dist[0] = 0;
		prev[0] = 0;
		return TRUE;
	}
	PSet neighbors;
	PVertex u;
	int i = 0;
	int alt = 0;
	PSet Q = SetCreate(cmpVertex, vertexClone, destroyVertex);
	if (Q == NULL) { return FALSE; }
	PVertex thisVertice = SetGetFirst(pGraph->vertexSet);
	for (i = 0; i < GraphGetNumberOfVertices(pGraph); i++) {// Initialization
		dist[i] = INT_MAX;
		prev[i] = 0;
		if (!(SetAdd(Q, thisVertice))) { //add all vertic to the set
			SetDestroy(Q);
			return FALSE; 
		}
		thisVertice = SetGetNext(pGraph->vertexSet);
	}
	dist[source] = 0;
	prev[source] = source;
	while (SetGetSize(Q) != 0) {// while Q is not empty
		u = SetGetFirst(Q);
		thisVertice = SetGetNext(Q);
		while (thisVertice != NULL) {//find vertex in Q with min dist
			if (dist[thisVertice->serialNumber] < dist[u->serialNumber]) { u = thisVertice; }
			thisVertice = SetGetNext(Q);
		}
		neighbors = GraphNeighborVertices(pGraph, u->serialNumber);//make set with all the neighbors 
		thisVertice = SetGetFirst(neighbors);
		while (thisVertice != NULL) {//run all the neighbors of u
			alt = findWeight(pGraph, thisVertice, u) + dist[u->serialNumber];
			if (alt < dist[thisVertice->serialNumber]) {// find shorter path
				dist[thisVertice->serialNumber] = alt;
				prev[thisVertice->serialNumber] = u->serialNumber;
			}
			thisVertice = SetGetNext(neighbors);
		}
		if (SetRemoveElement(Q, u) == FALSE) {//remove u from Q
			SetDestroy(Q);
			SetDestroy(neighbors);
			return FALSE;
		}
		SetDestroy(neighbors);
	}
	SetDestroy(Q);
	return TRUE;

}


