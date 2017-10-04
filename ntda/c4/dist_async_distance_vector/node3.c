#include <stdio.h>
#include <assert.h>
#include "rtpkt.h" 

int connectioncosts3[4] = { 7,  999,  2, 0};
struct distance_table dt3;

void rtinit3() 
{
    //[i,j] - to node i via direct neighbor j
    dt3.costs[0][0] = 999; dt3.costs[0][1] = 999; dt3.costs[0][2] = 999; dt3.costs[0][3] = 7;
    dt3.costs[1][0] = 999; dt3.costs[1][1] = 999; dt3.costs[1][2] = 999; dt3.costs[1][3] = 999;
    dt3.costs[2][0] = 999; dt3.costs[2][1] = 999; dt3.costs[2][2] = 999; dt3.costs[2][3] = 2;
    dt3.costs[3][0] = 999; dt3.costs[3][1] = 999; dt3.costs[3][2] = 999; dt3.costs[3][3] = 0;
    struct rtpkt pkt;
    pkt.sourceid = 3;
    pkt.destid = 2;
    pkt.mincost[0] = 7;
    pkt.mincost[1] = 999;
    pkt.mincost[2] = 2;
    pkt.mincost[3] = 0;
    tolayer2(pkt);
    pkt.destid = 0;
    tolayer2(pkt);
}

int mincost_to3(int i)
{
    return min(min(dt3.costs[i][0], dt3.costs[i][1]), min(dt3.costs[i][2], dt3.costs[i][3]));
}

void send_to3()
{
    struct rtpkt pkt;
    pkt.sourceid = 3;
    pkt.destid = 0;
    pkt.mincost[0] = mincost_to3(0);
    pkt.mincost[1] = mincost_to3(1);
    pkt.mincost[2] = mincost_to3(2);
    pkt.mincost[3] = mincost_to3(3);
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
}

void rtupdate3(struct rtpkt* rcvdpkt)
{
    assert(rcvdpkt);
    int send = 1;
    for (int i = 0; i < 4; ++i) {
        int min_cost = mincost_to3(i);
        int c = connectioncosts3[rcvdpkt->sourceid] + rcvdpkt->mincost[i];
        if (c < 999 && dt3.costs[i][rcvdpkt->sourceid] > c)
            dt3.costs[i][rcvdpkt->sourceid] = c;
        if (min_cost != mincost_to3(i)) {
            send = 0;
        }
    }
    if (send == 0)
        send_to3();
    printf("node3 min cost: (3, 0) -> %d (3, 1) -> %d (3, 2) -> %d (3, 3) -> %d \n", mincost_to3(0), mincost_to3(1), mincost_to3(2), mincost_to3(3));
}

void printdt3(struct distance_table* dtptr)
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}
