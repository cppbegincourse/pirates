#pragma once

template <typename T>
class Singleton {
public:
	static T* Instance();
protected:
	Singleton<T>();
private:
	static T* instance;
};

template <typename T>
T* Singleton<T>::instance = nullptr;

template <typename T>
T* Singleton<T>::Instance() {
	if (!instance) {
		instance = new T();
	}

	return instance;
}