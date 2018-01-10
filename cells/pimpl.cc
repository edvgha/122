#include <string>
#include "pimpl.h"

struct Widget::Impl {
    std::string name;
};

Widget::Widget() : pImpl(std::make_unique<Impl>())
{}

Widget::~Widget()
{}

Widget::Widget(Widget&&) = default;
Widget& Widget::operator = (Widget&&) = default;

Widget::Widget(const Widget& w) : pImpl(std::make_unique<Impl>(*w.pImpl))
{}

Widget& Widget::operator = (const Widget& w)
{
    *pImpl = *w.pImpl;
    return *this;
}
