#include "Singleton.h"
#include <iostream>

Singleton* Singleton::instance = nullptr;

Singleton::Singleton()
{
	std::cout << "Singleton instance created" << std::endl;
}

Singleton* Singleton::Instance()
{
    // Instantiate the singleton instance if it does not exist
    // and return the existing instance if it does
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}
