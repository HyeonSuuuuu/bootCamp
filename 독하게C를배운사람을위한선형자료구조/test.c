#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "ui.h"
#include "linkedList.h"

void InitDummyData(USERDATA* pTail)
{
	AddNewNodeAtTail(pTail, 10, "Hoon", "010-1111-2222");
	AddNewNodeAtTail(pTail, 13, "Gon", "010-2213-3341");
	AddNewNodeAtTail(pTail, 10, "GI", "010-1311-2622");
	AddNewNodeAtTail(pTail, 13, "NI", "010-2251-3333");
	AddNewNodeAtTail(pTail, 10, "WANG", "010-1311-2242");
	AddNewNodeAtTail(pTail, 13, "KIM", "010-7631-3942");
	AddNewNodeAtTail(pTail, 10, "JUNG", "010-3131-2822");
	AddNewNodeAtTail(pTail, 13, "HAN", "010-2121-3342");
	AddNewNodeAtTail(pTail, 10, "SON", "010-1212-7252");
	AddNewNodeAtTail(pTail, 13, "OH", "010-3253-3522");
}