// this file contains req info

#ifndef REQ_H
#define REQ_H

typedef struct {
	// must be one of (reqType, optType, startType, endType, transType)
	nodeType type;
	int elabId;
	int elabNum;
	int objId;
	nodeStages *stages;
	
	setData *startData;
	setData *endData;
} elabFullData;

typedef struct {
	
	// as in the case of Trans, this temp can be in the 
	// current stage or the next stage
	int isNextStage;
	int tempId;

	// these are the brackVars associated with this tempVar (usually just one)
	int cellName;

	// this is the connected cell names, the values newly 
	// associated with the tempVar from brackVars
	int isNeg;
	// conLastStage is myStage in elemInfo
	// conCellNames is myCellLinked in elemInfo
} tempElem;

typedef struct {
	int isNeg;
	int symId;
	// has cell and stage of elemInfo
} symElem;

typedef struct {

	// trans, req, opt, start, end name
	int desElabId;

	// number of elab (only used for Opt)
	int desElabNum;
	
	// desobj, board name
	int desObjId;

	// place this element is in the DesObj (width*y+x)
	int desObjPlace;

	int isNextStage;
	int myStage;
	// contains tempElem
	linkedList myTempList;
	// contains symElem
	linkedList mySymList;
	
	// all from DesObj cellData
	// contains int* cellName	
	linkedList myCellLinked;

	// sym list from board
	// need to go through each of these if it there is 
	// a connection between tempvars to make sure they match
	// linklist pointer
	linkedList cellSymList;

} elemInfo;

void atLeastOne(linkedList newVarList,linkedList clauseList);
void atMostOne(linkedList newVarList,linkedList clauseList);
int ifThen(linkedList varListA,linkedList varListB,linkedList clauseList);

void elabClauses(elabFullData *elab,linkedList desObjNodes,indexList *varList,linkedList clauseList);
void handleCell(linkedList symList,indexList *varList,linkedList clauseList,elemInfo *elem);

#endif
