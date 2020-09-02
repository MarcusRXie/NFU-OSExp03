//
// Created by Marcus.R.Xie on 2020/9/1.
//

#ifndef OSEXP03_INSTRUCTION_H
#define OSEXP03_INSTRUCTION_H

#include <iostream>
#include <vector>
#include "myrandom.h"
#include "page.h"

#define ADDR_START 0    //指令地址下限
#define ADDR_END 319   //指令地址上限
#define INST_NUM 320    //指令数量

using namespace std;

class Instruction {
private:
    vector<int> inst;
    vector<int> page;
    int page_size = 10;
public:
    void creRandomInst () {
        int buff[4];
        Random randnum;

        for (int num=0;num<INST_NUM;num+=4) {
//            cout << "Group#" << setw(2) << num/4 + 1 << "\t:";
            buff[0] = randnum.creRand(ADDR_START+1, ADDR_END-2);    //产生组内第一条顺序指令，选取地址时应确保至少有1个前地址，至少有2个后地址
            buff[1] = buff[0] + 1;  //依据第一条顺序指令产生第二条顺序指令
            buff[2] = randnum.creRand(ADDR_START, buff[0]-1);   //前地址部分产生一条指令
            buff[3] = randnum.creRand(buff[1], ADDR_END);   //后地址部分产生一条指令
            for (int i=0;i<4;i++) {
                inst.push_back(buff[i]);
                page.push_back(buff[i] / page_size);
            }
        }
    }

    void showInst () {  //显示指令地址序列
        for (int i=0;i<inst.size();i++) {
            cout << inst.at(i) << " ";
        }
        cout << endl;
    }

    void showPage () {  //显示页地址序列
        for (int i=0;i<page.size();i++) {
            cout << page.at(i) << " ";
        }
        cout << endl;
    }

    vector<int> &getInstSeq () {    //返回指令地址序列的引用
        return inst;
    }

    vector<int> &getPageSeq () {    //返回页地址序列的引用
        return page;
    }

};

#endif //OSEXP03_INSTRUCTION_H
