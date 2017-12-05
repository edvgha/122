#include "csapp.h"

/*
    struct hostent {
        char* h_name;       - Domain name
        char** h_aliases;   - Null terminated array of domin names
        int h_addrtype;     - Host address type
        int h_length;       - Length of an address, in bytes
        char** h_addr_list; - Null terminated array of in_addr structs
    };
*/

sem_t mutex;

void print(struct hostent* h)
{
    char** pp;
    struct in_addr addr;

    printf("Domain name %s\n", h->h_name);


    for (pp = h->h_aliases; *pp != NULL; ++pp)
        printf("Aliases %s\n", *pp);

    printf("Host address type %d\n", h->h_addrtype);

    printf("Length of an address %d\n", h->h_length);

    for (pp = h->h_addr_list; *pp != NULL; ++pp) {
        addr.s_addr = ((struct in_addr *)*pp)->s_addr;
        printf("address %s\n", inet_ntoa(addr));
    }
}

struct hostent *Gethostbyname_ts(const char *name)
{
    char** pp;
    char** pn;
    int s;
    struct hostent* h_new = NULL;

    /* Lock */
    P(&mutex);
    /* Get hostent structure */
    struct hostent* h_old = Gethostbyname(name);
    print(h_old);
    printf("----------------------------------\n");

    /* Create dynamic hostent structure object for deep copy */
    h_new = Malloc(sizeof(struct hostent));

    /* Deep copy domain name */
    h_new->h_name = Malloc(sizeof(char) * (strlen(h_old->h_name) + 1));
    strncpy(h_new->h_name, h_old->h_name, strlen(h_old->h_name) + 1);
    printf("Domain name: %s\n", h_new->h_name);

    /* Deep copy aliased domain names */
    for (s = 0, pp = h_old->h_aliases; *pp != NULL; ++pp, ++s);
    h_new->h_aliases = Malloc(sizeof(char *) * (s + 1));
    for (pn = h_new->h_aliases, pp = h_old->h_aliases; *pp != NULL; ++pp, ++pn) {
        *pn = Malloc(sizeof(char) * (strlen(*pp) + 1));
        strncpy(*pn, *pp, strlen(*pp) + 1);
    }
    *pn = NULL;
    for (pp = h_new->h_aliases; *pp != NULL; ++pp) {
        printf("Alias : %s\n", *pp);
    }

    /* Copy h_addrtype & h_length */ 
    h_new->h_addrtype = h_old->h_addrtype;
    h_new->h_length = h_old->h_length;
    printf("Addrtype : %d\n", h_new->h_addrtype);
    printf("AddrLength : %d\n", h_new->h_length);

    /* Deep copy address list */
    for (s = 0, pp = h_old->h_addr_list; *pp != NULL; ++pp, ++s);
    h_new->h_addr_list = Malloc(sizeof(char *) * (s + 1));
    for (pn = h_new->h_addr_list, pp = h_old->h_addr_list; *pp != NULL; ++pp, ++pn) {
        struct in_addr* ia = Malloc(sizeof(struct in_addr));
        ia->s_addr = ((struct in_addr *)*pp)->s_addr;
        *pn = (char *)ia;
    }
    *pn = NULL;
    for (pp = h_new->h_addr_list; *pp != NULL; ++pp) {
        struct in_addr addr;
        addr.s_addr = ((struct in_addr *)*pp)->s_addr;
        printf("address %s\n", inet_ntoa(addr));
    }

    /* Unlock */
    V(&mutex);
    return h_new;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("usage: %s <host name>\n", argv[0]);
        exit(0);
    }
    Sem_init(&mutex, 0, 1);
    struct hostent* h = Gethostbyname_ts(argv[1]);
    printf("----------------------------------\n");
    print(h);
}
