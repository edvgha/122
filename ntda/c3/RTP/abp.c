#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

/* ******************************************************************
   ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional or bidirectional
   data transfer protocols (from A to B. Bidirectional transfer of data
   is for extra credit and is not required).  Network properties:
   - one way network delay averages five time units (longer if there
   are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
   or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
   (although some can be lost).
 **********************************************************************/

#define BIDIRECTIONAL 0    /* change to 1 if you're doing extra credit */
/* and write a routine called B_output */

/* a "msg" is the data unit passed from layer 5 (teachers code) to layer  */
/* 4 (students' code).  It contains the data (characters) to be delivered */
/* to layer 5 via the students transport level protocol entities.         */
struct msg {
    char data[20];
};

/* a packet is the data unit passed from layer 4 (students code) to layer */
/* 3 (teachers code).  Note the pre-defined packet structure, which all   */
/* students must follow. */
struct pkt {
    int seqnum;
    int acknum;
    int checksum;
    char payload[20];
};

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
void tolayer3(int AorB,struct pkt packet);
void starttimer(int AorB, float increment);
void stoptimer(int AorB);
void tolayer5(int AorB, char datasent[20]);

#define   A    0
#define   B    1
#define WAIT_FOR_CALL_0_FROM_ABOVE 0
#define WAIT_FOR_ACK_0 1
#define WAIT_FOR_CALL_1_FROM_ABOVE 2
#define WAIT_FOR_ACK_1 3
#define WAIT_FOR_0_FROM_BELOW 0
#define WAIT_FOR_1_FROM_BELOW 1

int a_state = WAIT_FOR_CALL_0_FROM_ABOVE;
int b_state = WAIT_FOR_0_FROM_BELOW;

struct A_send_buffer {
    char data[2000];
    int idx_rcv;
    int idx_send;
};

struct A_send_buffer a_send_buffer;
struct pkt last_sent_paket;

union converter {
    uint16_t d;
    unsigned char c[2];
};

uint16_t get_checksum(int seq)
{
    uint32_t checksum = (uint32_t) seq;
    union converter con;
    for (int i = 0; i < 20; i += 2) {
        con.c[0] = a_send_buffer.data[a_send_buffer.idx_send + i];
        con.c[1] = a_send_buffer.data[a_send_buffer.idx_send + i + 1];
        checksum += con.d;
    }
    checksum &= 0xffff;
    uint16_t res = (uint16_t)checksum;
    return ~res;
}

int is_corrupted(struct pkt paket)
{
    uint32_t checksum = (uint32_t)paket.seqnum + (uint32_t)paket.acknum;
    union converter con;
    for (int i = 0; i < 20; i += 2) {
        con.c[0] = paket.payload[i];
        con.c[1] = paket.payload[i + 1];
        checksum += con.d;
    }
    checksum &= 0xffff;
    uint16_t res = (uint16_t)checksum;
    res += paket.checksum;
    return (res == 0xffff) ? 0 : 1;
}

struct pkt make_ack(int ack, int seq, int checksum)
{
    struct pkt package;
    package.acknum = ack;
    package.seqnum = seq;
    package.checksum = checksum;
    for (int i = 0; i < 20; ++i) {
        package.payload[i] = 0;
    }
    return package;
}

struct pkt make_pkt(int seq)
{
    struct pkt package;
    package.seqnum = seq;
    package.acknum = 0;
    package.checksum = get_checksum(seq);
    memcpy(package.payload, a_send_buffer.data + a_send_buffer.idx_send, 20);
    a_send_buffer.idx_send = (a_send_buffer.idx_send + 20) % 2000;
    last_sent_paket = package;
    return package;
}

/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
    //save msg
    memcpy(a_send_buffer.data + a_send_buffer.idx_rcv, message.data, 20);
    a_send_buffer.idx_rcv = (a_send_buffer.idx_rcv + 20) % 2000;
    if (a_state == WAIT_FOR_CALL_0_FROM_ABOVE) {
        printf(">>>> A_output WAIT_FOR_CALL_0_FROM_ABOVE\n");
        tolayer3(A, make_pkt(0));
        starttimer(A, 6);
        a_state = WAIT_FOR_ACK_0;
        return;
    } else if (a_state == WAIT_FOR_CALL_1_FROM_ABOVE) {
        printf(">>>> A_output WAIT_FOR_CALL_1_FROM_ABOVE\n");
        tolayer3(A, make_pkt(1));
        starttimer(A, 6);
        a_state = WAIT_FOR_ACK_1;
        return ;
    }
    printf(" -------> CAN'T SERVE\n");
}

void B_output(struct msg message)  /* need be completed only for extra credit */
{
    assert(1 == 2);
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
    if (a_state == WAIT_FOR_ACK_0) {
        if ((packet.acknum == 1 && packet.seqnum == 1) || 1 == is_corrupted(packet)) {
            printf(">>>> a_input wait_for_ack_0 curropted\n");
            return ;
        }
        if (0 == is_corrupted(packet) && (packet.acknum == 1 && packet.seqnum == 0)) {
            stoptimer(A);
            a_state = WAIT_FOR_CALL_1_FROM_ABOVE;
            printf(">>>> a_input wait_for_ack_0\n");
        }
    } else if (a_state == WAIT_FOR_ACK_1) {
        if ((packet.acknum == 1 && packet.seqnum == 0) || 1 == is_corrupted(packet)) {
            printf(">>>> a_input wait_for_ack_1 curropted\n");
            return ;
        }
        if (0 == is_corrupted(packet) && (packet.acknum == 1 && packet.seqnum == 1)) {
            stoptimer(A);
            a_state = WAIT_FOR_CALL_0_FROM_ABOVE;
            printf(">>>> a_input wait_for_ack_1\n");
        }
    }
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
    if (a_state == WAIT_FOR_ACK_0) {
        starttimer(A, 6);
        tolayer3(A, last_sent_paket);
        printf(">>>> a_timerinterrupt WAIT_FOR_ACK_0\n");
    } else if (a_state == WAIT_FOR_ACK_1) {
        starttimer(A, 6);
        tolayer3(A, last_sent_paket);
        printf(">>>> a_timerinterrupt WAIT_FOR_ACK_1\n");
    }
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
    a_send_buffer.idx_rcv = 0;
    a_send_buffer.idx_send = 0;
}


/* Note that with simplex transfer from a-to-B, there is no B_output() */

int checksum_ack_seq(int ack, int seqnum)
{
    uint16_t d = (uint16_t)ack + (uint16_t)(seqnum);
    d &= 0xffff;
    return ~d;
}

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
    if (b_state == WAIT_FOR_0_FROM_BELOW) {
        if (packet.seqnum == 0 && 0 == is_corrupted(packet)) {
            printf(">>>> b_input WAIT_FOR_0_FROM_BELOW ---> deliver data\n");
            tolayer5(B, packet.payload);
            tolayer3(B, make_ack(1, 0, checksum_ack_seq(1, 0)));
            b_state = WAIT_FOR_1_FROM_BELOW;
            return ;
        } else if (packet.seqnum == 1 || 1 == is_corrupted(packet)) {
            printf(">>>> b_input WAIT_FOR_0_FROM_BELOW corrupted\n");
            tolayer3(B, make_ack(1, 1, checksum_ack_seq(1, 1)));
            return ;
        }
    } else if (b_state == WAIT_FOR_1_FROM_BELOW) {
        if (packet.seqnum == 1 && 0 == is_corrupted(packet)) {
            printf(">>>> b_input WAIT_FOR_1_FROM_BELOW ---> deliver data\n");
            tolayer5(B, packet.payload);
            tolayer3(B, make_ack(1, 1, checksum_ack_seq(1, 1)));
            b_state = WAIT_FOR_0_FROM_BELOW;
            return ;
        } else if (packet.seqnum == 0 || 1 == is_corrupted(packet)) {
            printf(">>>> b_input WAIT_FOR_1_FROM_BELOW corrupted\n");
            tolayer3(B, make_ack(1, 0, checksum_ack_seq(1, 0)));
            return ;
        }
    }
}

/* called when B's timer goes off */
void B_timerinterrupt()
{
    return ;
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
    return ;
}


/*****************************************************************
 ***************** NETWORK EMULATION CODE STARTS BELOW ***********
 The code below emulates the layer 3 and below network environment:
 - emulates the tranmission and delivery (possibly with bit-level corruption
 and packet loss) of packets across the layer 3/4 interface
 - handles the starting/stopping of a timer, and generates timer
 interrupts (resulting in calling students timer handler).
 - generates message to be sent (passed from later 5 to 4)

 THERE IS NOT REASON THAT ANY STUDENT SHOULD HAVE TO READ OR UNDERSTAND
 THE CODE BELOW.  YOU SHOLD NOT TOUCH, OR REFERENCE (in your code) ANY
 OF THE DATA STRUCTURES BELOW.  If you're interested in how I designed
 the emulator, you're welcome to look at the code - but again, you should have
 to, and you defeinitely should not have to modify
 ******************************************************************/

struct event {
    float evtime;           /* event time */
    int evtype;             /* event type code */
    int eventity;           /* entity where event occurs */
    struct pkt *pktptr;     /* ptr to packet (if any) assoc w/ this event */
    struct event *prev;
    struct event *next;
};
struct event *evlist = NULL;   /* the event list */

/* possible events: */
#define  TIMER_INTERRUPT 0  
#define  FROM_LAYER5     1
#define  FROM_LAYER3     2

#define  OFF             0
#define  ON              1



int TRACE = 1;             /* for my debugging */
int nsim = 0;              /* number of messages from 5 to 4 so far */ 
int nsimmax = 0;           /* number of msgs to generate, then stop */
float time = 0.000;
float lossprob;            /* probability that a packet is dropped  */
float corruptprob;         /* probability that one bit is packet is flipped */
float lambda;              /* arrival rate of messages from layer 5 */   
int   ntolayer3;           /* number sent into layer 3 */
int   nlost;               /* number lost in media */
int ncorrupt;              /* number corrupted by media*/

void init();
void generate_next_arrival();
void insertevent(struct event* p);

int main()
{
    struct event *eventptr;
    struct msg  msg2give;
    struct pkt  pkt2give;

    int i,j;

    init();
    A_init();
    B_init();

    while (1) {
        eventptr = evlist;            /* get next event to simulate */
        if (eventptr==NULL)
            goto terminate;
        evlist = evlist->next;        /* remove this event from event list */
        if (evlist!=NULL)
            evlist->prev=NULL;
        if (TRACE>=2) {
            printf("\nEVENT time: %f,",eventptr->evtime);
            printf("  type: %d",eventptr->evtype);
            if (eventptr->evtype==0)
                printf(", timerinterrupt  ");
            else if (eventptr->evtype==1)
                printf(", fromlayer5 ");
            else
                printf(", fromlayer3 ");
            printf(" entity: %d\n",eventptr->eventity);
        }
        time = eventptr->evtime;        /* update time to next event time */
        if (nsim==nsimmax)
            break;                        /* all done with simulation */
        if (eventptr->evtype == FROM_LAYER5 ) {
            generate_next_arrival();   /* set up future arrival */
            /* fill in msg to give with string of same letter */    
            j = nsim % 26; 
            for (i=0; i<20; i++)  
                msg2give.data[i] = 97 + j;
            if (TRACE>2) {
                printf("          MAINLOOP: data given to student: ");
                for (i=0; i<20; i++) 
                    printf("%c", msg2give.data[i]);
                printf("\n");
            }
            nsim++;
            if (eventptr->eventity == A) 
                A_output(msg2give);  
            else
                B_output(msg2give);  
        }
        else if (eventptr->evtype ==  FROM_LAYER3) {
            pkt2give.seqnum = eventptr->pktptr->seqnum;
            pkt2give.acknum = eventptr->pktptr->acknum;
            pkt2give.checksum = eventptr->pktptr->checksum;
            for (i=0; i<20; i++)  
                pkt2give.payload[i] = eventptr->pktptr->payload[i];
            if (eventptr->eventity ==A)      /* deliver packet by calling */
                A_input(pkt2give);            /* appropriate entity */
            else
                B_input(pkt2give);
            free(eventptr->pktptr);          /* free the memory for packet */
        }
        else if (eventptr->evtype ==  TIMER_INTERRUPT) {
            if (eventptr->eventity == A) 
                A_timerinterrupt();
            else
                B_timerinterrupt();
        }
        else  {
            printf("INTERNAL PANIC: unknown event type \n");
        }
        free(eventptr);
    }

terminate:
    printf(" Simulator terminated at time %f\n after sending %d msgs from layer5\n",time,nsim);
    return 0;
}



void init()                         /* initialize the simulator */
{
    int i;
    float sum, avg;
    float jimsrand();


    printf("-----  Stop and Wait Network Simulator Version 1.1 -------- \n\n");
    printf("Enter the number of messages to simulate: ");
    scanf("%d",&nsimmax);
    printf("Enter  packet loss probability [enter 0.0 for no loss]:");
    scanf("%f",&lossprob);
    printf("Enter packet corruption probability [0.0 for no corruption]:");
    scanf("%f",&corruptprob);
    printf("Enter average time between messages from sender's layer5 [ > 0.0]:");
    scanf("%f",&lambda);
    printf("Enter TRACE:");
    scanf("%d",&TRACE);

    srand(9999);              /* init random number generator */
    sum = 0.0;                /* test random number generator for students */
    for (i=0; i<1000; i++)
        sum=sum+jimsrand();    /* jimsrand() should be uniform in [0,1] */
    avg = sum/1000.0;
    if (avg < 0.25 || avg > 0.75) {
        printf("It is likely that random number generation on your machine\n" ); 
        printf("is different from what this emulator expects.  Please take\n");
        printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
        exit(0);
    }

    ntolayer3 = 0;
    nlost = 0;
    ncorrupt = 0;

    time=0.0;                    /* initialize time to 0.0 */
    generate_next_arrival();     /* initialize event list */
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand() 
{
    double mmm = 2147483647;   /* largest int  - MACHINE DEPENDENT!!!!!!!!   */
    float x;                   /* individual students may need to change mmm */ 
    x = rand()/mmm;            /* x should be uniform in [0,1] */
    return(x);
}  

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/

void generate_next_arrival()
{
    double x;
    struct event *evptr;

    if (TRACE>2)
        printf("          GENERATE NEXT ARRIVAL: creating new arrival\n");

    x = lambda*jimsrand()*2;  /* x is uniform on [0,2*lambda] */
    /* having mean of lambda        */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtime =  time + x;
    evptr->evtype =  FROM_LAYER5;
    if (BIDIRECTIONAL && (jimsrand()>0.5) )
        evptr->eventity = B;
    else
        evptr->eventity = A;
    insertevent(evptr);
} 


void insertevent(struct event* p)
{
    struct event *q,*qold;

    if (TRACE>2) {
        printf("            INSERTEVENT: time is %lf\n",time);
        printf("            INSERTEVENT: future time will be %lf\n",p->evtime); 
    }
    q = evlist;     /* q points to header of list in which p struct inserted */
    if (q==NULL) {   /* list is empty */
        evlist=p;
        p->next=NULL;
        p->prev=NULL;
    }
    else {
        for (qold = q; q !=NULL && p->evtime > q->evtime; q=q->next)
            qold=q; 
        if (q==NULL) {   /* end of list */
            qold->next = p;
            p->prev = qold;
            p->next = NULL;
        }
        else if (q==evlist) { /* front of list */
            p->next=evlist;
            p->prev=NULL;
            p->next->prev=p;
            evlist = p;
        }
        else {     /* middle of list */
            p->next=q;
            p->prev=q->prev;
            q->prev->next=p;
            q->prev=p;
        }
    }
}

void printevlist()
{
    struct event *q;
    printf("--------------\nEvent List Follows:\n");
    for(q = evlist; q!=NULL; q=q->next) {
        printf("Event time: %f, type: %d entity: %d\n",q->evtime,q->evtype,q->eventity);
    }
    printf("--------------\n");
}



/********************** Student-callable ROUTINES ***********************/

/* called by students routine to cancel a previously-started timer */
void stoptimer(int AorB)
{
    struct event *q;

    if (TRACE>2)
        printf("          STOP TIMER: stopping timer at %f\n",time);
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q=evlist; q!=NULL ; q = q->next) 
        if ( (q->evtype==TIMER_INTERRUPT  && q->eventity==AorB) ) { 
            /* remove this event */
            if (q->next==NULL && q->prev==NULL)
                evlist=NULL;         /* remove first and only event on list */
            else if (q->next==NULL) /* end of list - there is one in front */
                q->prev->next = NULL;
            else if (q==evlist) { /* front of list - there must be event after */
                q->next->prev=NULL;
                evlist = q->next;
            }
            else {     /* middle of list */
                q->next->prev = q->prev;
                q->prev->next =  q->next;
            }
            free(q);
            return;
        }
    printf("Warning: unable to cancel your timer. It wasn't running.\n");
}


void starttimer(int AorB, float increment)
{

    struct event *q;
    struct event *evptr;

    if (TRACE>2)
        printf("          START TIMER: starting timer at %f\n",time);
    /* be nice: check to see if timer is already started, if so, then  warn */
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q=evlist; q!=NULL ; q = q->next)  
        if ( (q->evtype==TIMER_INTERRUPT  && q->eventity==AorB) ) { 
            printf("Warning: attempt to start a timer that is already started\n");
            return;
        }

    /* create future event for when timer goes off */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtime =  time + increment;
    evptr->evtype =  TIMER_INTERRUPT;
    evptr->eventity = AorB;
    insertevent(evptr);
} 

/************************** TOLAYER3 ***************/
void tolayer3(int AorB,struct pkt packet)
{
    struct pkt *mypktptr;
    struct event *evptr,*q;
    float lastime, x, jimsrand();
    int i;


    ntolayer3++;

    /* simulate losses: */
    if (jimsrand() < lossprob)  {
        nlost++;
        if (TRACE>0)    
            printf("          TOLAYER3: packet being lost\n");
        return;
    }  

    /* make a copy of the packet student just gave me since he/she may decide */
    /* to do something with the packet after we return back to him/her */ 
    mypktptr = (struct pkt *)malloc(sizeof(struct pkt));
    mypktptr->seqnum = packet.seqnum;
    mypktptr->acknum = packet.acknum;
    mypktptr->checksum = packet.checksum;
    for (i=0; i<20; i++)
        mypktptr->payload[i] = packet.payload[i];
    if (TRACE>2)  {
        printf("          TOLAYER3: seq: %d, ack %d, check: %d ", mypktptr->seqnum,
                mypktptr->acknum,  mypktptr->checksum);
        for (i=0; i<20; i++)
            printf("%c",mypktptr->payload[i]);
        printf("\n");
    }

    /* create future event for arrival of packet at the other side */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtype =  FROM_LAYER3;   /* packet will pop out from layer3 */
    evptr->eventity = (AorB+1) % 2; /* event occurs at other entity */
    evptr->pktptr = mypktptr;       /* save ptr to my copy of packet */
    /* finally, compute the arrival time of packet at the other end.
       medium can not reorder, so make sure packet arrives between 1 and 10
       time units after the latest arrival time of packets
       currently in the medium on their way to the destination */
    lastime = time;
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next) */
    for (q=evlist; q!=NULL ; q = q->next) 
        if ( (q->evtype==FROM_LAYER3  && q->eventity==evptr->eventity) ) 
            lastime = q->evtime;
    evptr->evtime =  lastime + 1 + 9*jimsrand();



    /* simulate corruption: */
    if (jimsrand() < corruptprob)  {
        ncorrupt++;
        if ( (x = jimsrand()) < .75)
            mypktptr->payload[0]='Z';   /* corrupt payload */
        else if (x < .875)
            mypktptr->seqnum = 999999;
        else
            mypktptr->acknum = 999999;
        if (TRACE>0)    
            printf("          TOLAYER3: packet being corrupted\n");
    }  

    if (TRACE>2)  
        printf("          TOLAYER3: scheduling arrival on other side\n");
    insertevent(evptr);
} 

void tolayer5(int AorB, char datasent[20])
{
    int i;  
    if (TRACE>2) {
        printf("          TOLAYER5: data received: ");
        for (i=0; i<20; i++)  
            printf("%c",datasent[i]);
        printf("\n");
    }

}
