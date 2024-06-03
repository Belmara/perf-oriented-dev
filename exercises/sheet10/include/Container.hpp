#include <cstddef>
#include "IteratorBase.hpp"

template<typename T>
class Container {
public:
    virtual ~Container() = default;

    virtual void insert(size_t index, const T &value) = 0;
    virtual void remove(size_t index) = 0;
    virtual T& operator[](size_t index) = 0;
    virtual size_t get_size() const = 0;

    class Iterator: public IteratorBase<T> {
    public:
        virtual ~Iterator() = default;
    };

    virtual Iterator* begin() = 0;
    virtual Iterator* end() = 0;
};
