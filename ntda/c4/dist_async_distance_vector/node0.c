#include <stdio.h>
#include <assert.h>
#include "rtpkt.h"

struct distance_table dt0;

int connectioncosts0[4] = {0, 1, 3, 7};

void rtinit0() 
{
    //[i,j] - to node i via direct neighbor j
    dt0.costs[0][0] = 0; dt0.costs[0][1] = 999; dt0.costs[0][2] = 999; dt0.costs[0][3] = 999;
    dt0.costs[1][0] = 1; dt0.costs[1][1] = 999; dt0.costs[1][2] = 999; dt0.costs[1][3] = 999;
    dt0.costs[2][0] = 3; dt0.costs[2][1] = 999; dt0.costs[2][2] = 999; dt0.costs[2][3] = 999;
    dt0.costs[3][0] = 7; dt0.costs[3][1] = 999; dt0.costs[3][2] = 999; dt0.costs[3][3] = 999;
    struct rtpkt pkt;
    pkt.sourceid = 0;
    pkt.destid = 1;
    pkt.mincost[0] = 0;
    pkt.mincost[1] = 1;
    pkt.mincost[2] = 3;
    pkt.mincost[3] = 7;
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
    pkt.destid = 3;
    tolayer2(pkt);
}

int mincost_to0(int i)
{
    return min(min(dt0.costs[i][0], dt0.costs[i][1]), min(dt0.costs[i][2], dt0.costs[i][3]));
}

void send_to0()
{
    struct rtpkt pkt;
    pkt.sourceid = 0;
    pkt.destid = 1;
    pkt.mincost[0] = mincost_to0(0);
    pkt.mincost[1] = mincost_to0(1);
    pkt.mincost[2] = mincost_to0(2);
    pkt.mincost[3] = mincost_to0(3);
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
    pkt.destid = 3;
    tolayer2(pkt);

}

void rtupdate0(struct rtpkt* rcvdpkt)
{
    assert(rcvdpkt);
    int send = 1;
    for (int i = 0; i < 4; ++i) {
        int min_cost = mincost_to0(i);
        int c = connectioncosts0[rcvdpkt->sourceid] + rcvdpkt->mincost[i];
        if (c < 999 && dt0.costs[i][rcvdpkt->sourceid] > c)
            dt0.costs[i][rcvdpkt->sourceid] = c;
        if (min_cost != mincost_to0(i)) {
            send = 0;
        }
    }
    if (send == 0)
        send_to0();
    printf("node0 min cost: (0, 0) -> %d (0, 1) -> %d (0, 2) -> %d (0, 3) -> %d \n", mincost_to0(0), mincost_to0(1), mincost_to0(2), mincost_to0(3));
}

void printdt0(struct distance_table* dtptr)
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid,int newcost)   

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}
