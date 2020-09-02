//
// Created by Marcus.R.Xie on 2020/9/2.
//

#ifndef OSEXP03_RAM_H
#define OSEXP03_RAM_H

#include <vector>

using namespace std;

class Ram {
private:
    vector<int> block;  //物理块，记录已调入RAM的页面号
    int size = 2;   //默认RAM容量
public:
    Ram (int size) {
        this->size = size;
    }

    bool isEmpty () {
        return block.empty();
    }

    bool isFull () {
        if (block.size() == size) {
            return true;
        } else {
            return false;
        }
    }

    int isExist (int block_num) {
        if (block.empty()) {
            return -1;
        }
        for (int pos=0;pos<block.size();pos++) {
            if (block.at(pos) == block_num) {
                return pos;
            }
        }
        return -1;
    }

    bool remove (int dest_pos) {    //删除RAM中下标为dest_pos的页面
        if (dest_pos < 0 || dest_pos >= block.size()) { //异常处理
            return false;
        } else {
            vector<int>::iterator it;
            int cur_pos = 0;
            for (it=block.begin();it<block.end();it++,cur_pos++) {
                if (cur_pos == dest_pos) {
                    it = block.erase(it);   //通过迭代器做删除处理
                }
            }
            return true;
        }
    }

    vector<int> &getBolck () {  //获取物理块vector的引用
        return block;
    }
};

#endif //OSEXP03_RAM_H
