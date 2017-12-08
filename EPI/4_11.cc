#include <iostream>
#include <cmath>

/**
 * Rectangle intersection
 */

struct Rectangle 
{
    double left_up_x_;
    double left_up_y_;
    double right_down_x_;
    double right_down_y_;

    Rectangle(double lx = NAN, double ly = NAN,
              double rx = NAN, double ry = NAN)
    : left_up_x_(lx)
    , left_up_y_(ly)
    , right_down_x_(rx)
    , right_down_y_(ry)
    {}

    void print() const 
    {
        std::cout << "(" << left_up_x_ << ", " << left_up_y_ << ")" << " -- "
                  << "(" << right_down_x_ << ", " << right_down_y_ << ")\n";
    }
};

Rectangle intersection(const Rectangle& r1, const Rectangle& r2)
{
    double x1 = NAN;
    double x2 = NAN;
    double y1 = NAN;
    double y2 = NAN;

    if (r1.left_up_x_ < r2.left_up_x_) {
        if (r1.right_down_x_ >= r2.left_up_x_) {
            x1 = r2.left_up_x_;
            if (r1.right_down_x_ > r2.right_down_x_) {
                x2 = r2.right_down_x_;
            } else {
                x2 = r1.right_down_x_;
            }
        }
    } else {
        if (r2.right_down_x_ >= r1.left_up_x_) {
            x1 = r1.left_up_x_;
            if (r2.right_down_x_ > r1.right_down_x_) {
                x2 = r1.right_down_x_;
            } else {
                x2 = r2.right_down_x_;
            }
        }
    }

    if (r1.right_down_y_ < r2.right_down_y_) {
        if (r1.left_up_y_ >= r2.right_down_y_) {
            y1 = r2.right_down_y_;
            if (r1.left_up_y_ > r2.left_up_y_) {
                y2 = r2.left_up_y_;
            } else {
                y2 = r1.left_up_y_;
            }
        }
    } else {
        if (r2.left_up_y_ >= r1.right_down_y_) {
            y1 = r1.right_down_y_;
            if (r2.left_up_y_ > r1.left_up_y_) {
                y2 = r1.left_up_y_;
            } else {
                y2 = r2.left_up_y_;
            }
        }
    }

    Rectangle ret;
    if (std::isnan(x1) || std::isnan(x2) || std::isnan(y1) || std::isnan(y2)) {
        return ret;
    }
    ret.left_up_x_ = x1 > x2 ? x2 : x1;
    ret.left_up_y_ = y1 > y2 ? y1 : y2;
    ret.right_down_x_ = x1 > x2 ? x1 : x2;
    ret.right_down_y_ = y1 > y2 ? y2 : y1;
    return ret;
}

int main()
{
    {
        Rectangle r1(1, 3, 7, 1), r2(3, 5, 5, 0);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(0, 1, 1, 0), r2(1, 5, 5, 1);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(0, 1, 1, 0), r2(3, 3, 4, 2);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(0, 5, 5, 0), r2(5, 3, 6, 0);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(0, 5, 5, 0), r2(4, 6, 10, 4);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(16, 22, 22, 0), r2(12, 17, 18, 2);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(0, 10, 10, 0), r2(10, 10, 15, 0);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(0, 20, 10, 5), r2(0, 10, 5, 0);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
    {
        Rectangle r1(7, 22, 15, 5), r2(15, 10, 20, 0);
        Rectangle r = intersection(r1, r2);
        r.print();
    }
}
