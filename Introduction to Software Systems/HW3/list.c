#include "list.h"

typedef struct Node_
{
	PElem pElem;
	struct Node_* pNext;
} Node,*PNode;

//*********************************************************************************
//* function name: createNode
//* Description  : creats new node
//* Parameters   : pElem- a pointer to element
//                 pNext- a pointer to the next element
//                 cloneFunc- a pointer to the element clone function
//* Return value : PNode,a pointer to the new node
//*********************************************************************************
PNode createNode(PElem pElem, PNode pNext,CLONE_FUNC cloneFunc) {
	PNode pNode = (PNode)malloc(sizeof(Node));
	if (pNode == NULL) return NULL;
	PElem newElem = cloneFunc(pElem);//creat clone
	if (newElem == NULL) {
		free(pNode);
		return NULL;
	}
	pNode->pElem = newElem;
	pNode->pNext = pNext;
	return pNode;
}


//*********************************************************************************
//* function name: destroyNode
//* Description  : destroy a given node
//* Parameters   : pNode- a pointer to the node
//                 destroyFunc- a pointer to the element destroy function
//* Return value : Result- SUCCESS for destroy success or FAILURE for destroy failure
//*********************************************************************************
Result destroyNode(PNode pNode,DESTROY_FUNC destroyFunc) { 
	if (pNode == NULL) return FAIL;
	if(pNode->pElem!=NULL) destroyFunc(pNode->pElem); //destroy the inside element
	free(pNode);
	return SUCCESS;
}


struct List_
{
	PNode firstNode;
	PNode ip;
	CLONE_FUNC cloneFunc;
	DESTROY_FUNC destroyFunc;
	int count;					
};



/*Interface functions*/

//*********************************************************************************
//* function name: ListCreate
//* Description  : creats new list
//* Parameters   : destroyFunc- a pointer to the element destroy function
//                 cloneFunc- a pointer to the element clone function
//* Return value : PList, a pointer to the new list, null for fail
//*********************************************************************************
PList ListCreate(CLONE_FUNC cloneFunc, DESTROY_FUNC destroyFunc) { 
	PList pList = (PList)malloc(sizeof(struct List_));
	if (pList == NULL) return NULL;
	pList->cloneFunc = cloneFunc;
	pList->destroyFunc = destroyFunc;
	pList->ip = NULL;
	pList->firstNode = NULL;
	pList->count = 0;
	return pList;
}


//*********************************************************************************
//* function name: ListAdd
//* Description  : add given element to given list
//* Parameters   : pElem- a pointer to the element
//                 PList- a pointer to the list
//* Return value : Result- SUCCESS for add success or FAILURE for add failure
//*********************************************************************************
Result ListAdd(PList pList, PElem pElem) {    
	PNode pNode = createNode(pElem, pList->firstNode,pList->cloneFunc);
	if (pNode == NULL) return FAIL;
	pList->firstNode = pNode;
	pList->ip = NULL;
	pList->count = pList->count + 1;
	return SUCCESS;
}


//*********************************************************************************
//* function name: ListDestroy
//* Description  : destroy a given list
//* Parameters   : pList- a pointer to the list
//* Return value : None
//*********************************************************************************
void ListDestroy(PList pList) {
	if (pList == NULL) return;
	pList->ip = pList->firstNode;
	PNode tempNode = NULL;
	while (pList->ip != NULL) {//run on the list and destroy the nodes
		tempNode = pList->ip->pNext;
		if (destroyNode(pList->ip, pList->destroyFunc) == FAIL) return;
		pList->ip = tempNode;	
	}
	free(pList);
}


//*********************************************************************************
//* function name: ListGetFirst
//* Description  : return a pointer to the top element in a given list, set the ip to the first element
//* Parameters   : pList- a pointer to the list
//* Return value : PElem, a pointer to the first element
//*********************************************************************************
PElem ListGetFirst(PList pList) {
	if (pList == NULL) return NULL;
	pList->ip = pList->firstNode;
	if(pList->ip==NULL) return NULL;
	return pList->ip->pElem;
}


//*********************************************************************************
//* function name: ListGetNext
//* Description  : setp in the ip and return a pointer to the ip element in a given list
//* Parameters   : pList- a pointer to the list
//* Return value : PElem, a pointer to the ip element
//*********************************************************************************
PElem ListGetNext(PList pList) {
	if (pList == NULL) return NULL;
	if (pList->ip == NULL) return NULL;
	if (pList->ip->pNext == NULL) return NULL; 
	pList->ip = pList->ip->pNext;
	return pList->ip->pElem;
}


//*********************************************************************************
//* function name: ListRemove
//* Description  : remove the ip element from a given list
//* Parameters   : pList- a pointer to the list
//* Return value : Result- SUCCESS for remove success or FAILURE for remove failure
//*********************************************************************************
Result ListRemove(PList pList) {
	if (pList == NULL) return FAIL;
	if(pList->ip==NULL) return FAIL;
	PNode tempNode = pList->firstNode;
	if (tempNode == NULL) return FAIL;
	if (tempNode == pList->ip) {//if the ip is the first element
		pList->firstNode = pList->ip->pNext;
		if (destroyNode(pList->ip, pList->destroyFunc) == FAIL) return FAIL;
		pList->ip = NULL;
		(pList->count)--;
		return SUCCESS;
	}
	while (tempNode->pNext != pList->ip) {//find the node to remove
		tempNode = tempNode->pNext;
	}
	tempNode->pNext = pList->ip->pNext;//remove the node
	if (destroyNode(pList->ip, pList->destroyFunc) == FAIL) return FAIL;
	pList->ip = NULL;
	(pList->count)--;
	return SUCCESS;
}


//*********************************************************************************
//* function name: ListGetSize
//* Description  : return the size of thr list
//* Parameters   : pList- a pointer to the list
//* Return value : int, the size of thr list
//*********************************************************************************
int ListGetSize(PList pList) {
	if (pList == NULL) return 0;
	return pList->count;
}
