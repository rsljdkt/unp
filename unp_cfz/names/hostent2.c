#include "unp.h"

int main(int argc, const char *argv[])
{
    char *ptr, **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent *hptr;
    unsigned int ip;

    while (--argc > 0)
    {
        ptr = *++argv;
        Inet_pton(AF_INET, ptr, &ip);
        if ((hptr = gethostbyaddr(&ip, 4, AF_INET)) == NULL)
        {
            err_msg("gethostbyname error for host: %s: %s",
                    ptr, hstrerror(h_errno));
            continue;
        }
        printf("official hostname: %s\n", hptr->h_name);

        for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
        {
            printf("\talias: %s\n", *pptr);
        }

        switch (hptr->h_addrtype)
        {
            case AF_INET:
                pptr = hptr->h_addr_list;
                for (; *pptr != NULL; pptr++)
                    printf("\taddress: %s\n",
                            Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
                break;
            default:
                err_ret("unknown address type");
                break;
        }
    }
    return 0;
}

