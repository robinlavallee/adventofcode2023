
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Point {
    long long  x;
    long long y;
};

struct Formula {
    double m;
    double b;
};

struct Velocity {
    int x;
    int y;
};

struct Hailstone {
    Point p;
    Formula f;
    Velocity v;
};

std::vector<Hailstone> stones;

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::string line;
        while (getline(newfile, line)) {
            // 19, 13, 30 @ -2,  1, -2

            auto at = line.find('@');
            auto left = line.substr(0, at);
            auto right = line.substr(at + 2);

            left += ",";
            right += ",";

            auto comma = left.find(",");
            auto x = std::stoll(left.substr(0, comma));
            left = left.substr(comma + 1);
            comma = left.find(",");
            auto y = std::stoll(left.substr(0, comma));
            left = left.substr(comma + 1);
            comma = left.find(",");
            auto z = std::stoll(left.substr(0, comma));

            Hailstone stone;
            stone.p = {x, y};

            comma = right.find(",");
            auto vx = std::stoi(right.substr(0, comma));
            right = right.substr(comma + 1);
            comma = right.find(",");
            auto vy = std::stoi(right.substr(0, comma));
            right = right.substr(comma + 1);
            comma = right.find(",");
            auto vz = std::stoi(right.substr(0, comma));

            stone.v = {vx, vy};

            // y = mx + b
            // y - b = mx
            // (y - b) / x = m

            stone.f.m = (double)vy / (double)vx;
            stone.f.b = (double)y - stone.f.m * (double)x;

            std::cout << "m=" << stone.f.m << " " << "b=" << stone.f.b << std::endl;

            stones.push_back(stone);
        }

        double min = 200000000000000;
        double max = 400000000000000;

        unsigned int count = 0;
        for (int i = 0; i < stones.size(); i++) {
            for (int j = i + 1; j < stones.size(); j++) {
                // find intersection point
                // y = m1x + b1
                // y = m2x + b2

                //std::cout << "Hailstone " << i << " and " << j << std::endl;

                double left = stones[i].f.b - stones[j].f.b;
                double right = stones[j].f.m - stones[i].f.m;
                if (abs(right) < 0.0000001) {
                    //std::cout << "Parallel" << std::endl << std::endl;
                    continue;
                }
                
                double x = left / right;
                double y = stones[i].f.m * x + stones[i].f.b;

                //std::cout << "Stones intersect at (" << x << ", " << y << ")" << std::endl;

                if (x >= min && x <= max && y >= min && y <= max) {
                    if ((x > stones[i].p.x && stones[i].v.x < 0) || (y > stones[i].p.y && stones[i].v.y < 0) || (x < stones[i].p.x && stones[i].v.x > 0) || (y < stones[i].p.y && stones[i].v.y > 0)) {
                        //std::cout << "In the past for first stone" << std::endl;
                    } else if ((x > stones[j].p.x && stones[j].v.x < 0) || (y > stones[j].p.y && stones[j].v.y < 0) || (x < stones[j].p.x && stones[j].v.x > 0) || (y < stones[j].p.y && stones[j].v.y > 0)) {
                        //std::cout << "In the past for second stone" << std::endl;
                    } else {
                        //std::cout << "Within test area" << std::endl;
                        count++;
                    }
                } else {
                    //std::cout << "Outside test area" << std::endl;
                }

                //std::cout << std::endl;
            }
        }

        std::cout << count << std::endl;

        newfile.close();
    }

    return 0;
}


int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}
