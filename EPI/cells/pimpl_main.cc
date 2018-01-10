#include "pimpl.h"

int main()
{
    Widget w;
    Widget w1(std::move(w));
}
