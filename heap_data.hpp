#include <memory> 
#include <cstdio>

struct HeapData {
public:
    HeapData() : ptr(std::make_unique<int>(0)) {
        std::puts("HeapData() -> allocated");
    }

    ~HeapData() {
        if (ptr) {
            std::puts("~HeapData() -> deallocated");
        } else {
            std::puts("~HeapData()");
        }
    }

    HeapData(const HeapData& other) : ptr(std::make_unique<int>(*other.ptr)) {
        std::puts("HeapData(const HeapData&) -> allocated");
    }

    HeapData& operator=(const HeapData& other) {
        if (this != &other) {
            ptr = std::make_unique<int>(*other.ptr);
            std::puts("HeapData& operator=(const HeapData&) -> allocated");
        }
        return *this;
    }

    HeapData(HeapData&& other) : ptr(std::move(other.ptr)) {
        std::puts("HeapData(HeapData&&)");
    }

    HeapData& operator=(HeapData&& other) {
        if (this != &other) {
            ptr = std::move(other.ptr);
            std::puts("HeapData& operator=(HeapData&&)");
        }
        return *this;
    }

    bool operator==(const HeapData& o) const noexcept {
        if (!ptr || !o.ptr) return ptr.get() == o.ptr.get();
        return *ptr == *o.ptr;
    }

    size_t hash() const noexcept {
        return ptr ? std::hash<int>{}(*ptr) : 0;
    }
private:
    std::unique_ptr<int> ptr;
};

template<> struct std::hash<HeapData> {
    size_t operator()(const HeapData& h) const noexcept { return h.hash(); }
};
