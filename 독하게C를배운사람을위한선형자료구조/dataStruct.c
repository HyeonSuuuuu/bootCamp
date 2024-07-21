#include <conio.h>
#include "linkedList.h"
#include "ui.h"
#include "test.h"
#include "dataStruct.h"


int main() {
	USERDATA headNode = { 0, "__Dummy Head__"};
	USERDATA tailNode = { 0, "__Dummy Tail__" };
	InitList(&headNode, &tailNode);
	InitDummyData(&tailNode);
	EventLoopRun(&headNode, &tailNode);


	ReleaseList(&headNode, &tailNode);
}
