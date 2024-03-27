//Будникова Валерия Павловна М8О-207Б
//Вариант 31(Фигуры: треугольник, 6-угольник, 7-угольник)
#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <thread>

template <class T>
class Server {
    private:
        Server(){};
        std::vector<std::function<void(T &)>> subscribers;
        std::queue<T> message_queue;
        std::mutex mutex;
    public:
        using subscriber_type = std::function<void(T &)>;
        static Server &get() {
            static Server instance;
            return instance;
        }
        void register_subscriber(const subscriber_type &sub) {
            std::lock_guard<std::mutex> lock(mutex);
            subscribers.push_back(sub);
        }
        void publish(const T &msg) {
            std::lock_guard<std::mutex> lock(mutex);
            message_queue.push(msg);
        }
        void run() {
            while (!false) {
                if (!message_queue.empty()) {
                    std::lock_guard<std::mutex> lock(mutex);
                    T fig = message_queue.front();
                    if (fig.empty()) {
                        break;
                    }
                    message_queue.pop();
                    for (auto sub : subscribers)
                        try {
                            sub(fig);
                        } catch (std::exception &ex) { 
                            std::cout << "Exception in subscriber:" << ex.what() << std::endl;
                        }
                } else {
                    std::this_thread::yield();
                }
            }
        }
};