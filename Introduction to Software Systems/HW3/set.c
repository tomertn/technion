#include "set.h"

typedef struct _Set
{
	PList setElements;
	COMP_FUNC cmpFunc;
} Set;

PSet SetCreate(COMP_FUNC cmpFunc, CLONE_FUNC cloneFunc, DESTROY_FUNC destroyFunc)
{
	PSet pSet =(PSet)malloc(sizeof(*pSet));
	if(pSet == NULL)
	{
		return pSet;
	}
	pSet->cmpFunc = cmpFunc;
	pSet->setElements = ListCreate(cloneFunc,destroyFunc);
	if(pSet->setElements == NULL)
	{
		free(pSet);
		return NULL;
	}
	return pSet;
}

void SetDestroy (PSet pSet)
{
	if(pSet == NULL)
	{
		return ;
	}
	ListDestroy(pSet->setElements);
	free(pSet);
}

Bool SetAdd (PSet pSet, PElem pElem){
	if(pSet == NULL || pElem == NULL)
	{
		return FALSE;
	}
	if(SetFindElement(pSet, pElem) != NULL)
	{
		return FALSE;

	}
	ListAdd(pSet->setElements, pElem);
	return TRUE;
}

PElem SetGetFirst(PSet pSet)
{
	return ListGetFirst(pSet->setElements);
}

PElem SetGetNext (PSet pSet){
	return ListGetNext(pSet->setElements);
}

PElem SetFindElement (PSet pSet, PElem pElem)
{
	if( pSet == NULL || pElem == NULL )
	{
		return NULL;
	}
	PList pList = pSet->setElements;
	PElem result = ListGetFirst(pList);
	while( result != NULL && pSet->cmpFunc(pElem,result) != TRUE)
	{
		result  = ListGetNext(pList);
	}
	return result;
}

int SetGetSize(PSet pSet)
{
	if( pSet == NULL || pSet->setElements == NULL )
	{
		return 0;
	}
	return ListGetSize(pSet->setElements);
}

Bool SetRemoveElement(PSet pSet, PElem pElem)
{
	if( pSet == NULL || pElem == NULL)
	{
		return FALSE;
	}
	if (SetFindElement(pSet,pElem) == NULL)
	{
		return FALSE;
	}
	if( ListRemove(pSet->setElements) )
	{
		return TRUE;
	}
	return FALSE;
}
