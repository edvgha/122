#include <mutex>
#include <memory>

#include <iostream>

template <typename T>
class threadsafe_list
{
    private:
        struct node
        {
            public:
                std::mutex m;
                std::shared_ptr<T> data;
                std::unique_ptr<node> next;

            public:
                node(): next() {}
                node(T const& value): data(std::make_shared<T>(value)) {}
        };

    private:
        node head;

    public:
        threadsafe_list() {}
        ~threadsafe_list()
        {
            remove_if([](node const &) { return true; });
        }
        threadsafe_list(const threadsafe_list& other) = delete;
        threadsafe_list& operator = (const threadsafe_list& other) = delete;

    public:
        void push_back(T const& value)
        {
            std::unique_ptr<node> new_node(new node(value));
            std::lock_guard<std::mutex> lk(head.m);
            new_node->next = std::move(head.next);
            head.next = std::move(new_node);
        }

        template <typename Function>
        void for_each(Function f)
        {
            node* current = &head;
            std::unique_lock<std::mutex> lk(head.m);
            while (node* const next = current->next.get()) {
                std::unique_lock<std::mutex> next_lk(next->m);
                lk.unlock();
                f(*next->data);
                current = next;
                lk = std::move(next_lk);
            }
        }

        template <typename Predicate>
        std::shared_ptr<T> find_first_if(Predicate p)
        {
            node* current = &head;
            std::unique_lock<std::mutex> lk(head.m);
            while (node* const next = current->next.get()) {
                std::unique_lock<std::mutex> next_lk(next->m);
                lk.unlock();
                if (p(*next->data)) {
                    return next->data;
                }
                current = next;
                lk = std::move(next_lk);
            }
            return std::shared_ptr<T>();
        }

        template <typename Predicate>
        void remove_if(Predicate p)
        {
            node* current = &head;
            std::unique_lock<std::mutex> lk(head.m);
            while (node* const next = current->next.get()) {
                std::unique_lock<std::mutex> next_lk(next->m);
                if (p(*next->data)) {
                    std::unique_ptr<node> old_next = std::move(current->next);
                    current -> next = std::move(next->next);
                    next_lk.unlock();
                } else {
                    lk.unlock();
                    current = next;
                    lk = std::move(next_lk);
                }
            }
        }
};

/*********************************/

int main()
{
    threadsafe_list<int> list;

    list.push_back(1);
    list.push_back(1);
    list.push_back(3);
    list.push_back(3);
    list.push_back(4);
    list.push_back(7);
    list.push_back(5);
    list.push_back(5);

    list.for_each([](int i) { std::cout << i << std::endl;});
    std::cout << "find_first_if" << std::endl;
    auto ptr = list.find_first_if([](int i) { return i == 3;});
    if (ptr) {
        std::cout << *ptr << std::endl;
    }
    std::cout << "-------------" << std::endl;
    list.remove_if([](int i) { return i == 4 || i == 7; });
    list.for_each([](int i) { std::cout << i << std::endl;});
    
}
