//
// Created by Marcus.R.Xie on 2020/9/1.
//

#ifndef OSEXP03_MYRANDOM_H
#define OSEXP03_MYRANDOM_H

#include <cstdlib>
#include <ctime>

class Random {  //Random类：用于生成随机数
public:
    Random () {
        srand((int)time(NULL));
    }

    int creRand (int min, int max) {    //产生一个[min,max]区间内的随机数（含区间端点）
        return (rand()%(max-min+1))+min;
    }

};

#endif //OSEXP03_MYRANDOM_H
