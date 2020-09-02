#include <iostream>
#include <iomanip>
#include "instruction.h"
#include "page.h"

#define MAX_RAM_SIZE 32 //内存大小上限（可修改）

using namespace std;

int main () {
    Instruction inst;
    inst.creRandomInst();   //按规则随机生成320条指令
    //inst.showInst();
    //inst.showPage();
    for (int ram_size=2;ram_size<=MAX_RAM_SIZE;ram_size++) {
        //当前实验使用的RAM物理块大小（最多能容纳的页面数）
        cout << "Ram size:" << left << setw(3) << ram_size << '\t';

        //OPT算法命中率
        cout << "OPT:" << left << setw(8) << setprecision(5) << OPT(inst.getPageSeq(), ram_size) << '\t';

        //FIFO算法命中率
        cout << "FIFO:" << left << setw(8) << setprecision(5) << FIFO(inst.getPageSeq(), ram_size) << '\t';

        //LRU算法命中率
        cout << "LRU:" << left << setw(8) << setprecision(5) << LRU(inst.getPageSeq(), ram_size) << endl;
    }

    return 0;
}

