#include "pch.h"

#include <gtest/gtest.h>
#include "queue_list.h"

// 1. Базовый тест конструктора
TEST(QueueListTest, DefaultConstructorCreatesEmptyQueue) {
    Queue<int> queue;
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.maxSize(), 20);
}

// 2. Проверка основного функционала push/front/back
TEST(QueueListTest, PushAndFrontBackWorkCorrectly) {
    Queue<int> queue(5);
    queue.push(10);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 10); // front и back одинаковы для одного элемента

    queue.push(20);
    EXPECT_EQ(queue.front(), 10); // front остается первым
    EXPECT_EQ(queue.back(), 20);  // back становится последним
}

// 3. Проверка FIFO порядка (очередь)
TEST(QueueListTest, QueueFollowsFIFO) {
    Queue<int> queue(5);
    queue.push(1);
    queue.push(2);
    queue.push(3);

    // Должны получать элементы в порядке добавления
    EXPECT_EQ(queue.front(), 1);
    queue.pop();

    EXPECT_EQ(queue.front(), 2);
    queue.pop();

    EXPECT_EQ(queue.front(), 3);
}

// 4. Проверка исключений при пустой очереди
TEST(QueueListTest, ThrowsWhenPoppingEmptyQueue) {
    Queue<int> queue;
    EXPECT_THROW(queue.pop(), std::logic_error);
}

TEST(QueueListTest, ThrowsWhenFrontOnEmptyQueue) {
    Queue<int> queue;
    EXPECT_THROW(queue.front(), std::logic_error);
    EXPECT_THROW(queue.back(), std::logic_error);
}

// 5. Проверка исключений при полной очереди
TEST(QueueListTest, ThrowsWhenPushingFullQueue) {
    Queue<int> queue(2);
    queue.push(1);
    queue.push(2);

    EXPECT_TRUE(queue.isFull());
    EXPECT_THROW(queue.push(3), std::logic_error);
}

// 6. Проверка работы после pop (можно добавлять снова)
TEST(QueueListTest, CanPushAfterPop) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.push(3);

    // Удаляем первый элемент
    queue.pop(); // теперь в очереди [2, 3]
    EXPECT_EQ(queue.size(), 2);

    // Можно добавить новый элемент
    queue.push(4); // теперь [2, 3, 4]
    EXPECT_EQ(queue.size(), 3);

    // Проверяем порядок
    EXPECT_EQ(queue.front(), 2);
    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    queue.pop();
    EXPECT_EQ(queue.front(), 4);
}

// 7. Проверка методов size и maxSize
TEST(QueueListTest, SizeAndMaxSizeWorkCorrectly) {
    Queue<int> queue(5);
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.maxSize(), 5);

    queue.push(1);
    EXPECT_EQ(queue.size(), 1);

    queue.push(2);
    queue.push(3);
    EXPECT_EQ(queue.size(), 3);

    queue.pop();
    EXPECT_EQ(queue.size(), 2);
}

// 8. Проверка isFull для разных случаев
TEST(QueueListTest, IsFullWorksCorrectly) {
    Queue<int> queue(3);
    EXPECT_FALSE(queue.isFull());

    queue.push(1);
    EXPECT_FALSE(queue.isFull());

    queue.push(2);
    queue.push(3);
    EXPECT_TRUE(queue.isFull());
}

// 9. Проверка работы с разными типами данных
TEST(QueueListTest, WorksWithStrings) {
    Queue<std::string> queue(3);
    queue.push("first");
    queue.push("second");

    EXPECT_EQ(queue.front(), "first");
    EXPECT_EQ(queue.back(), "second");

    queue.pop();
    EXPECT_EQ(queue.front(), "second");
}

// 10. Проверка граничного случая - очередь размером 1
TEST(QueueListTest, WorksWithSizeOne) {
    Queue<int> queue(1);
    EXPECT_TRUE(queue.isEmpty());

    queue.push(42);
    EXPECT_EQ(queue.front(), 42);
    EXPECT_EQ(queue.back(), 42);
    EXPECT_TRUE(queue.isFull());

    EXPECT_THROW(queue.push(43), std::logic_error);

    queue.pop();
    EXPECT_TRUE(queue.isEmpty());
    queue.push(100);
    EXPECT_EQ(queue.front(), 100);
}

// 11. Проверка clear
TEST(QueueListTest, ClearEmptiesQueue) {
    Queue<int> queue(5);
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.isEmpty());
    queue.clear();
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0);
}

// 12. Проверка копирования
TEST(QueueListTest, CopyConstructorWorks) {
    Queue<int> queue1(5);
    queue1.push(1);
    queue1.push(2);
    queue1.push(3);

    Queue<int> queue2(queue1); // копирование

    EXPECT_EQ(queue2.size(), 3);
    EXPECT_EQ(queue2.maxSize(), 5);

    // Проверяем, что это разные объекты
    queue2.pop();
    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue1.size(), 3); // оригинал не изменился
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}