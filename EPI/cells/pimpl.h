#include <memory>

class Widget {
    public :
        Widget();
        ~Widget();
        Widget(Widget&&);
        Widget& operator = (Widget&&);
        Widget(const Widget&);
        Widget& operator = (const Widget& );
    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
};
