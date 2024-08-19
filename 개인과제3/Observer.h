#pragma once

#include <vector>
#include <algorithm>
class IObserver {
public:
	virtual ~IObserver() = default;
	virtual void notify() = 0;
};


class Observable {
public:
	virtual ~Observable() = default;

	void addObserver(IObserver* observer) { observers.push_back(observer); }
	void removeObserver(IObserver* observer)
	{
		observers.erase(std::remove(begin(observers), end(observers), observer), end(observers));
	}
protected:
	void notifyAllObservers()
	{
		for (auto* observer : observers)
			observer->notify();
	}

private:
	std::vector<IObserver*> observers;
};

class ObservableSubject : public Observable {
public:
	void modifyData() {
		notifyAllObservers();
	}
};