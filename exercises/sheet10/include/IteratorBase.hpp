#pragma once

template<typename T>
class IteratorBase {
public:
    virtual T &read() const = 0;

    virtual void write(const T &value) = 0;

    virtual void insert(const T &value) = 0;

    virtual void remove() = 0;

    virtual bool is_end() const = 0;

    virtual void next() = 0;

    virtual ~IteratorBase() = default;
};