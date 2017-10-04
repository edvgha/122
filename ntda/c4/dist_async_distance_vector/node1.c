#include <stdio.h>
#include <assert.h>
#include "rtpkt.h"

int connectioncosts1[4] = { 1,  0,  1, 999 };

struct distance_table dt1;

void rtinit1() 
{
    //[i,j] - to node i via direct neighbor j
    dt1.costs[0][0] = 999; dt1.costs[0][1] = 1; dt1.costs[0][2] = 999; dt1.costs[0][3] = 999;
    dt1.costs[1][0] = 999; dt1.costs[1][1] = 0; dt1.costs[1][2] = 999; dt1.costs[1][3] = 999;
    dt1.costs[2][0] = 999; dt1.costs[2][1] = 1; dt1.costs[2][2] = 999; dt1.costs[2][3] = 999;
    dt1.costs[3][0] = 999; dt1.costs[3][1] = 999; dt1.costs[3][2] = 999; dt1.costs[3][3] = 999;
    struct rtpkt pkt;
    pkt.sourceid = 1;
    pkt.destid = 0;
    pkt.mincost[0] = 1;
    pkt.mincost[1] = 0;
    pkt.mincost[2] = 1;
    pkt.mincost[3] = 999;
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
}

int mincost_to1(int i)
{
    return min(min(dt1.costs[i][0], dt1.costs[i][1]), min(dt1.costs[i][2], dt1.costs[i][3]));
}

void send_to1()
{
    struct rtpkt pkt;
    pkt.sourceid = 1;
    pkt.destid = 0;
    pkt.mincost[0] = mincost_to1(0);
    pkt.mincost[1] = mincost_to1(1);
    pkt.mincost[2] = mincost_to1(2);
    pkt.mincost[3] = mincost_to1(3);
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
}

void rtupdate1(struct rtpkt* rcvdpkt)
{
    assert(rcvdpkt);
    int send = 1;
    for (int i = 0; i < 4; ++i) {
        int min_cost = mincost_to1(i);
        int c = connectioncosts1[rcvdpkt->sourceid] + rcvdpkt->mincost[i];
        if (c < 999 && dt1.costs[i][rcvdpkt->sourceid] > c)
            dt1.costs[i][rcvdpkt->sourceid] = c;
        if (min_cost != mincost_to1(i)) {
            send = 0;
        }
    }
    if (send == 0)
        send_to1();
    printf("node1 min cost: (1, 0) -> %d (1, 1) -> %d (1, 2) -> %d (1, 3) -> %d \n", mincost_to1(0), mincost_to1(1), mincost_to1(2), mincost_to1(3));
}

void printdt1(struct distance_table* dtptr)
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}

void linkhandler1(int linkid, int newcost)   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}
