#pragma once

#include "Observer.h"

class MyList;
class MyFile;

class StatisticsUI : public IObserver {
public:
	StatisticsUI(MyList& rList, MyFile& rFile);
	void display(void);
	void notify(void);

private:
	MyList& list;
	MyFile& file;
};