#include <stdio.h>
#include <assert.h>
#include "rtpkt.h" 

int connectioncosts2[4] = { 3,  1,  0, 2};
struct distance_table dt2;

void rtinit2() 
{
    //[i,j] - to node i via direct neighbor j
    dt2.costs[0][0] = 999; dt2.costs[0][1] = 999; dt2.costs[0][2] = 3; dt2.costs[0][3] = 999;
    dt2.costs[1][0] = 999; dt2.costs[1][1] = 999; dt2.costs[1][2] = 1; dt2.costs[1][3] = 999;
    dt2.costs[2][0] = 999; dt2.costs[2][1] = 999; dt2.costs[2][2] = 0; dt2.costs[2][3] = 999;
    dt2.costs[3][0] = 999; dt2.costs[3][1] = 999; dt2.costs[3][2] = 2; dt2.costs[3][3] = 999;
    struct rtpkt pkt;
    pkt.sourceid = 2;
    pkt.destid = 0;
    pkt.mincost[0] = 3;
    pkt.mincost[1] = 1;
    pkt.mincost[2] = 0;
    pkt.mincost[3] = 2;
    tolayer2(pkt);
    pkt.destid = 1;
    tolayer2(pkt);
    pkt.destid = 3;
    tolayer2(pkt);
}
int mincost_to2(int i)
{
    return min(min(dt2.costs[i][0], dt2.costs[i][1]), min(dt2.costs[i][2], dt2.costs[i][3]));
}

void send_to2()
{
    struct rtpkt pkt;
    pkt.sourceid = 2;
    pkt.destid = 0;
    pkt.mincost[0] = mincost_to2(0);
    pkt.mincost[1] = mincost_to2(1);
    pkt.mincost[2] = mincost_to2(2);
    pkt.mincost[3] = mincost_to2(3);
    tolayer2(pkt);
    pkt.destid = 1;
    tolayer2(pkt);
    pkt.destid = 3;
    tolayer2(pkt);
}

void rtupdate2(struct rtpkt* rcvdpkt)
{
    assert(rcvdpkt);
    int send = 1;
    for (int i = 0; i < 4; ++i) {
        int min_cost = mincost_to2(i);
        int c = connectioncosts2[rcvdpkt->sourceid] + rcvdpkt->mincost[i];
        if (c < 999 && dt2.costs[i][rcvdpkt->sourceid] > c)
            dt2.costs[i][rcvdpkt->sourceid] = c;
        if (min_cost != mincost_to2(i)) {
            send = 0;
        }
    }
    if (send == 0)
        send_to2();
    printf("node2 min cost: (2, 0) -> %d (2, 1) -> %d (2, 2) -> %d (2, 3) -> %d \n", mincost_to2(0), mincost_to2(1), mincost_to2(2), mincost_to2(3));
}

void printdt2(struct distance_table* dtptr)
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}
