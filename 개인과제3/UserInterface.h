#pragma once
#include "Observer.h"

class MyList;
class MyFile;

class UserInterface : public IObserver
{
public:
	UserInterface(MyList& rList, MyFile& rFile);
	~UserInterface(void);
	void add(void);
	int printUI(void);
	int run(void);
	void search(void);
	void remove(void);
	void printAll(void);
	void save(void);
	void edit(void);
	void notify(void);

protected:
	MyList& list;
	MyFile& file;
	size_t maxOutput = 25;
};