#pragma once

template <typename _T>
class Singleton
{
// parent class of Keyboard.h
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
	Singleton(const Singleton& r) = default;
	Singleton& operator = (const Singleton& r) = default;

public:
	static _T* getIns() {
		static _T inst;
		return &inst; // return the instance of the singleton
	}
};