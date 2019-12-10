#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include <utility>

#define EPSILON 0.001

class Point {
public:
	Point() : x(0), y(0) {}
	Point(double x_, double y_) : x(x_), y(y_) {} 
	double x;
	double y;
};

Point getMidPoint(const Point& a, const Point& b) {
	Point center = Point( (b.x + a.x) / 2, (b.y + a.y) / 2 );
	return center;
}

double getLength(const Point& a, const Point& b) {
	return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2) );
}

class Diagonal {
public:
	Diagonal(const Point& a, const Point& b);
	Diagonal(const Point& center_, double length_) : center(center_), length(length_) {} 

	// Center of Diagonal
	Point center;

	double length;
};

Diagonal::Diagonal(const Point& a, const Point& b) {
	center = getMidPoint(a, b);
	length = getLength(a, b);

}


bool operator==(const Diagonal& a, const Diagonal& b) {
	return std::abs(a.center.x - b.center.x) < EPSILON &&
			std::abs(a.center.y - b.center.y) < EPSILON &&
			std::abs(a.length - b.length) < EPSILON;	
}

int Round(double n) {
	return (int)n;
}

// Hash functions obtained from geeksforgeeks
class MyHashFunctor {
public:
	unsigned int operator() (const Diagonal& d) const {
		unsigned int hash = 1315423911;
		std::string key = std::to_string(Round(d.center.x)) + std::to_string(Round(d.center.y)) + std::to_string(Round(d.length));
		for(unsigned int i = 0; i < key.length(); i++)
			hash ^= ((hash << 5) + key[i] + (hash >> 2));
		return hash;
	}
};

int main(int argc, char* argv[]) {
	// Make sure an input file has been given
	assert(argc == 2);
	// Open input file
	std::ifstream read;
	read.open(std::string(argv[1]));
	assert(read.good());

	std::vector<Point> points;
	double x, y;

	while(read >> x) {
		read >> y;
		points.push_back(Point(x, y));
	}

	typedef std::unordered_map<Diagonal, int, MyHashFunctor> hashmap;

	hashmap diagonals;
	int answer = 0;
	for(unsigned int i = 0 ; i < points.size(); ++i) {
		for(unsigned int j = i + 1; j < points.size(); ++j) {
			Diagonal d = Diagonal(points[i], points[j]);
			unsigned int index = diagonals.bucket(d);
			for(hashmap::local_iterator itr = diagonals.begin(index); itr != diagonals.end(index); ++itr) {
				if(d == itr->first){
					answer += itr->second;
					++itr->second;
				}
			}
			diagonals.insert(std::make_pair(d, 1));
		}
	}

	std::cout << "A total of " << answer << " rectangle(s) can be made with the provided points.\n";
}