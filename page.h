//
// Created by Marcus.R.Xie on 2020/9/1.
//

#ifndef OSEXP03_PAGE_H
#define OSEXP03_PAGE_H

#include <vector>
#include <queue>
#include "ram.h"

using namespace std;

double FIFO (vector<int> &page, int ram_size);    //先进先出置换算法
double OPT (vector<int> &page, int ram_size);     //最佳置换算法
double LRU (vector<int> &page, int ram_size);     //最近最久未使用算法
int nextAccess (vector<int>page, int cur_pos, int dest_page);   //计算某一页面下一次出现在页面号序列中的位置，适用于OPT算法

double FIFO (vector<int> &page, int ram_size) { //此算法下RAM与队列近似，遵循先进先出规则
    Ram ram(ram_size);
    int success = 0;    //命中次数
    int failure = 0;    //未命中（中断）次数
    vector<int>::iterator it;
    for (int cur_page_index=0;cur_page_index<page.size();cur_page_index++) {
        int cur_page_num = page.at(cur_page_index); //获得即将访问的页面号
        if (!ram.isFull() && ram.isExist(cur_page_num) == -1) { //RAM未满时读取未命中，发生缺页中断
            ram.getBolck().push_back(cur_page_num); //调入所需页面
            failure++;  //记录中断次数
        } else if (ram.isExist(cur_page_num) >= 0) {    //读取命中
            success++;  //记录命中次数
        } else if (ram.isFull() && ram.isExist(cur_page_num) == -1) {   //RAM已满时读取未命中，发生缺页中断
            ram.remove(0);  //依据FIFO，换出最先调入RAM的页面
            ram.getBolck().push_back(cur_page_num); //调入新页面
            failure++;
        }
    }

    return (double)success / (success + failure);   //计算命中率
}

double OPT (vector<int> &page, int ram_size) {
    Ram ram(ram_size);
    int success = 0;
    int failure = 0;
    vector<int>::iterator it_ram;
    for (int cur_page_index=0;cur_page_index<page.size();cur_page_index++) {
        int cur_page_num = page.at(cur_page_index);
        if (!ram.isFull() && ram.isExist(cur_page_num) == -1) {
            ram.getBolck().push_back(cur_page_num);
            failure++;
        } else if (ram.isExist(cur_page_num) >= 0) {
            success++;
        } else if (ram.isFull() && ram.isExist(cur_page_num) == -1) {
            int next_pos;
            vector<int> next_pos_vector;    //存放RAM中已有页面的下一次访问时间（实际为下一次出现在页面序列中的位置）
            for (it_ram=ram.getBolck().begin();it_ram<ram.getBolck().end();it_ram++) {  //寻找位置并记录
                next_pos = nextAccess(page, cur_page_index, *it_ram);
                next_pos_vector.push_back(next_pos);
            }
            int max_index = 0;  //记录访问时间（位置）靠后的页面下标
            for (int i=0;i<next_pos_vector.size();i++) {    //寻找访问时间（位置）靠后的页面下标
                if (next_pos_vector.at(i) > next_pos_vector.at(max_index)) {
                    max_index = i;
                }
            }
            ram.remove(max_index);  //调出此前找到的页面
            ram.getBolck().push_back(cur_page_num); //调入新页面
            failure++;
            next_pos_vector.clear();    //清除先前记录的位置，为下一次页面调入做准备
        }
//        for (it_ram=ram.getBolck().begin();it_ram<ram.getBolck().end();it_ram++) {
//            cout << *it_ram << " ";
//        }
//        cout << endl;
    }

    return (double) success / (success + failure);
}

double LRU (vector<int> &page, int ram_size) {  //本算法使用特殊栈保存已调入页面
    Ram ram(ram_size);
    int success = 0;
    int failure = 0;
    vector<int>::iterator it;
    for (int cur_page_index = 0; cur_page_index < page.size(); cur_page_index++) {
        int cur_page_num = page.at(cur_page_index);
        if (!ram.isFull() && ram.isExist(cur_page_num) == -1) {
            ram.getBolck().push_back(cur_page_num);
            failure++;
        } else if (ram.isExist(cur_page_num) >= 0) {    //将命中的页面调入栈顶
            int pos = ram.isExist(cur_page_num);    //获取命中页面下标
            ram.remove(pos);    //暂时删除该页面
            ram.getBolck().push_back(cur_page_num); //将该页面重新压入栈顶
            success++;
        } else if (ram.isFull() && ram.isExist(cur_page_num) == -1) {
            ram.remove(0);  //从栈底调出页面
            ram.getBolck().push_back(cur_page_num); //在栈顶压入新页面，实现调入
            failure++;
        }
//        for (it=ram.getBolck().begin();it<ram.getBolck().end();it++) {
//            cout << *it << " ";
//        }
//        cout << endl;
    }
    return (double) success / (success + failure);
}

int nextAccess (vector<int>page, int cur_pos, int dest_page) {
    int next_pos;
    for (next_pos=cur_pos+1;next_pos<page.size();next_pos++) {
        if (page.at(next_pos) == dest_page) {
            break;
        }
    }
    return next_pos;
}



#endif //OSEXP03_PAGE_H
