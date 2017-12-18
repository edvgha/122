#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

template <typename T>
class Queue {
private:
	std::vector<T> queue_;
	size_t size_;
	int front_;
	int back_;

public:
	Queue(size_t n = 100): queue_(n, T())
						 , size_(n)
						 , front_(-1)
						 , back_(-1)
	{}
	T dequeue() noexcept (false)
	{
		if (size() == 0) {
			throw std::logic_error("queue is empty");
		}
		return queue_[++back_ % size_];
	}
	void enqueue(T t)
	{
		if (size() == size_) {
			//TODO
		} 
		queue_[++front_ % size_] = t;

	}
	size_t size() const
	{
		return std::abs(front_ - back_);
	}

	void display() const
	{
		assert(size_ == queue_.size());
		std::cout << "front : " << front_ << std::endl;
		std::cout << "back : " << back_ << std::endl;
		for (auto el : queue_)
			std::cout << el << ", ";
	}

};

int main(int argc, char const *argv[])
{
	Queue<int> queue(4);
	try {
		queue.enqueue(1);
		queue.enqueue(2);
		queue.dequeue();
		queue.dequeue();
		queue.enqueue(3);
		queue.enqueue(4);
		queue.enqueue(5);
		queue.enqueue(6);
		queue.enqueue(7);


		queue.display();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}