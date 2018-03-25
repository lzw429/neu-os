#ifndef _FS_H
#define _FS_H

#include <linux/sched.h>

#define READ 0
#define WRITE 1
#define READA 2
#define WRITEA 3

#define MAJOR(a) (((unsigned)(a))>>8)

struct buffer_head {
    char *b_data;  /* pointer to data block 1024Byte */
    unsigned long b_blocknr; /* block number */
    unsigned short b_dev; /* device no */
    unsigned char b_uptodate;
    unsigned char b_dirt;   /* 0-clean 1-dirty */
    unsigned char b_count;  /* users using this block */
    unsigned char b_lock;   /* 0-unlock 1-lock */
    struct task_struct *b_wait;
    struct buffer_head *b_prev;
    struct buffer_head *b_next;
    struct buffer_head *b_prev_free;
    struct buffer_head *b_next_free;
};

// 内存中的i节点结构。
struct m_inode {
    unsigned short i_mode;    // 文件类型和属性(rwx 位)。
    unsigned short i_uid;        // 用户id（文件拥有者标识符）。
    unsigned long i_size;        // 文件大小（字节数）。
    unsigned long i_mtime;    // 修改时间（自1970.1.1:0 算起，秒）。
    unsigned char i_gid;        // 组id(文件拥有者所在的组)。
    unsigned char i_nlinks;    // 文件目录项链接数。
    unsigned short i_zone[9];    // 直接(0-6)、间接(7)或双重间接(8)逻辑块号。
/* these are in memory also */
    struct task_struct *i_wait;    // 等待该i 节点的进程。
    unsigned long i_atime;    // 最后访问时间。
    unsigned long i_ctime;    // i 节点自身修改时间。
    unsigned short i_dev;        // i 节点所在的设备号。
    unsigned short i_num;        // i 节点号。
    unsigned short i_count;    // i 节点被使用的次数，0 表示该i 节点空闲。
    unsigned char i_lock;        // 锁定标志。
    unsigned char i_dirt;        // 已修改(脏)标志。
    unsigned char i_pipe;        // 管道标志。
    unsigned char i_mount;    // 安装标志。
    unsigned char i_seek;        // 搜寻标志(lseek 时)。
    unsigned char i_update;    // 更新标志。
};

#endif
