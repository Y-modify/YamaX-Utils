#pragma once

#include <vector>

class robot
{
public:
    robot();
    std::vector<servo> servos;

private:
    char name[40];
    int age;
};
