#pragma once
class Singleton {
protected:
    static Singleton* instance;

    Singleton(); // Protected constructor

    // Preventing copying and assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:

    virtual ~Singleton() = default;

    // Static method to control the access to the singleton instance
    static Singleton* Instance();
};
