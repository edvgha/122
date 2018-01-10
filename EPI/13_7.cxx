#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct Interval
{
public:
	struct EndPoint 
	{
		bool is_closed;
		int val;

		bool operator < (const EndPoint& ep) const
		{
			if (val != ep.val) 
				return val < ep.val;
			return is_closed && !ep.is_closed;
		}

		void print() const
		{
			std::cout << ">>> " << std::boolalpha << is_closed << ' ' << val << std::endl;
		}
	};

public:
	bool operator < (const Interval& e) const
	{
		if (left.val != e.left.val) 
			return left.val < e.left.val;
		return left.is_closed && !left.is_closed;
	}

	void print() const 
	{
		std::cout << std::boolalpha << left.is_closed << ' ' << right.is_closed << ' ' << left.val << ' ' << right.val << std::endl;
	}

	
	EndPoint left;
	EndPoint right;
};

void merge(std::vector<Interval>& intervals, const Interval& i2)
{
	Interval& i1 = intervals[intervals.size() - 1];

	if ((i1.left.val == i2.left.val) && (i1.left.is_closed || i2.left.is_closed))
		i1.left.is_closed = true;
	else if ((i1.right.val == i2.left.val) && (i1.right.is_closed || i2.left.is_closed)) 
		i1.right = i2.right;
	else if (((i1.right.val == i2.left.val) && (!i1.right.is_closed && !i2.left.is_closed)) || i1.right.val < i2.left.val)
		intervals.push_back(i2);
	else if (i1.right.val > i2.left.val) {
		if (i1.right.val < i2.right.val) {
			i1.right.val = i2.right.val;
			i1.right.is_closed = i2.right.is_closed;
		} else if ((i1.right.val == i2.right.val) && (i1.right.is_closed || i2.right.is_closed)) {
			i1.right.is_closed = true;
		}
	}

}


std::vector<Interval> Union( std::vector<Interval>& intervals)
{
	

	if (intervals.size() == 1 || intervals.empty()) 
		return std::vector<Interval>(intervals.begin(), intervals.end());

	std::sort(intervals.begin(), intervals.end());

	for (auto el : intervals) 
		el.print();
	std::cout << "-------" << std::endl;
	std::vector<Interval> res;
	res.push_back(intervals[0]);

	for (size_t i = 1; i < intervals.size(); ++i) {
		merge(res, intervals[i]);
	}
	return res;
}

int main()
{
	std::vector<Interval> intervals({{{false, 0}, {false, 3}}, {{true, 1}, {true, 1}}, {{true, 2}, {true, 4}}, {{true, 3}, {false, 4}}, {{true, 5}, {false, 7}}, {{true, 7}, {false, 8}}, {{true, 8}, {false, 11}}, {{false, 9}, {true, 11}}, {{false, 13}, {false, 15}}, {{false, 12}, {true, 16}}, {{true, 12}, {true, 14}}, {{false, 16}, {false, 17}}});

	auto res = Union(intervals);

	std::cout << " --- result ---" << std::endl;
	for (auto x : res) 
		x.print();
}