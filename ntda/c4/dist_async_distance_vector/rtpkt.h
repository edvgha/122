#pragma once
/*
    +--+     1     +--+
    |0 |-----------|1 |
    +--+           +--+
     |  +           |
     |    +  3      |
    7|      +       |1
     |        +     |
     |          +   |
    +--+     2    ++--+
    |2 |-----------|3 |
    +--+           +--+
*/

struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
};

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
};

void tolayer2(struct rtpkt packet);
int min(int a, int b);
