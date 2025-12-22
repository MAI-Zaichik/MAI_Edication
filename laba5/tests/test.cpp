#include <gtest/gtest.h>
#include <memory_resource>
#include "../include/queue.hpp"
#include "../include/mem_res.hpp"

TEST(QueueTest, BasicIntOperations) {
    Fmem_res mr(1024);
    pmr_queue<int> queue(&mr);

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);

    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);

    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.size(), 2);
}

TEST(QueueTest, ComplexTypeOperations) {
    struct Person {
        std::string name;
        int age;
        Person(std::string n = "", int a = 0) : name(std::move(n)), age(a) {}
        bool operator==(const Person& other) const {
            return name == other.name && age == other.age;
        }
    };

    Fmem_res mr(2048);
    pmr_queue<Person> queue(&mr);

    queue.push(Person("Alice", 30));
    queue.push(Person("Bob", 25));

    EXPECT_EQ(queue.front().name, "Alice");
    EXPECT_EQ(queue.front().age, 30);
    EXPECT_EQ(queue.back().name, "Bob");
    EXPECT_EQ(queue.back().age, 25);
}

TEST(QueueTest, IteratorTest) {
    Fmem_res mr(1024);
    pmr_queue<int> queue(&mr);

    queue.push(10);
    queue.push(20);
    queue.push(30);

    auto it = queue.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, queue.end());

    std::vector<int> values;
    for (const auto& val : queue) {
        values.push_back(val);
    }
    EXPECT_EQ(values, std::vector<int>({10, 20, 30}));
}

TEST(QueueTest, CopyAndMoveSemantics) {
    Fmem_res mr(1024);
    
    pmr_queue<int> original(&mr);
    original.push(1);
    original.push(2);
    original.push(3);

    pmr_queue<int> copy(original);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);

    pmr_queue<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 3);
    EXPECT_TRUE(original.empty());
}

TEST(QueueTest, MemoryReuse) {
    Fmem_res mr(512);
    pmr_queue<std::string> queue(&mr);

    queue.push("first");
    queue.push("second");
    queue.pop();

    queue.push("third");
    EXPECT_EQ(queue.front(), "second");
    EXPECT_EQ(queue.back(), "third");
}

TEST(QueueTest, ClearTest) {
    Fmem_res mr(1024);
    pmr_queue<int> queue(&mr);

    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.size(), 3);
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, ExceptionSafety) {
    Fmem_res mr(100);
    
    pmr_queue<int> queue(&mr);
    
    queue.push(1);
    queue.push(2);
    
    EXPECT_NO_THROW({
        try {
            queue.push(3);
        } catch (const std::bad_alloc&) {
        }
    });
}