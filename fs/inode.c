#include <string.h>
#include <sys/stat.h>

#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <asm/system.h>

struct m_inode inode_table[NR_INODE] = {0}; // 内存中i 节点表（NR_INODE=32 项）
// m_inode定义在include/linux/fs.h

static void read_inode(struct m_inode *inode);

static void write_inode(struct m_inode *inode);

//// 等待指定的i 节点可用。
// 如果i 节点已被锁定，则将当前任务置为不可中断的等待状态。直到该i 节点解锁。
static _inline void wait_on_inode(struct m_inode *inode) {
    cli();
    while (inode->i_lock)
        sleep_on(&inode->i_wait);
    sti();
}

//// 对指定的i 节点上锁（锁定指定的i 节点）。
// 如果i 节点已被锁定，则将当前任务置为不可中断的等待状态。直到该i 节点解锁，然后对其上锁。
static _inline void lock_inode(struct m_inode *inode) {
    cli();
    while (inode->i_lock)
        sleep_on(&inode->i_wait);
    inode->i_lock = 1;    // 置锁定标志。
    sti();
}

//// 对指定的i 节点解锁。
// 复位i 节点的锁定标志，并明确地唤醒等待此i 节点的进程。
static _inline void unlock_inode(struct m_inode *inode) {
    inode->i_lock = 0;
    wake_up(&inode->i_wait);
}

//// 释放内存中设备dev 的所有i 节点。
// 扫描内存中的i 节点表数组，如果是指定设备使用的i 节点就释放之。
void invalidate_inodes(int dev) {
    int i;
    struct m_inode *inode;

    inode = 0 + inode_table;        // 让指针首先指向i 节点表指针数组首项。
    for (i = 0; i < NR_INODE; i++, inode++) {    // 扫描i 节点表指针数组中的所有i 节点。
        wait_on_inode(inode);                // 等待该i 节点可用（解锁）。
        if (inode->i_dev == dev) {            // 如果是指定设备的i 节点，则
            if (inode->i_count)                // 如果其引用数不为0，则显示出错警告；
                printk("inode in use on removed disk\n\r");
            inode->i_dev = inode->i_dirt = 0;    // 释放该i 节点(置设备号为0 等)。
        }
    }
}
