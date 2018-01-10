#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

class Connection
{
    private:
        std::once_flag connection_init_flag;

    private:
        void open_connection()
        {
            std::cout << "open_connection\n";
        }
        void do_send()
        {
            std::cout << "do_send\n";
        }
        void do_recv()
        {
            std::cout << "do_recv\n";
        }
    public:
        void send() 
        {
            std::call_once(connection_init_flag, &Connection::open_connection, this);
            do_send();
        }
        void recv()
        {
            std::call_once(connection_init_flag, &Connection::open_connection, this);
            do_recv();
        }
};

int main()
{
    Connection conn;
    std::thread t0(&Connection::send, &conn);
    std::thread t1(&Connection::recv, &conn);
    std::thread t2(&Connection::send, &conn);
    std::thread t3(&Connection::recv, &conn);
    std::thread t4(&Connection::send, &conn);
    std::thread t5(&Connection::recv, &conn);
    t0.join(); t1.join();
    t2.join(); t3.join();
    t4.join(); t5.join();
}
