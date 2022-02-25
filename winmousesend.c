#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <string.h>

#define PORT 5555
#define SERVER "192.168.1.5"
#define BUFLEN 2*sizeof(int)
int send_data(int x, int y)
{
        return 0;
}

int main()
{
        struct sockaddr_in si_other;
        int s, slen = sizeof(si_other);
        //int buf[BUFLEN];
        char message[BUFLEN];
        WSADATA wsa;
        printf("\nInitialising Winsock...");
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
                printf("Failed. Error Code : %d", WSAGetLastError());
                exit(EXIT_FAILURE);
        }
        printf("Initialised.\n");

        //create socket
        if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
                printf("socket() failed with error code : %d",
                       WSAGetLastError());
                exit(EXIT_FAILURE);
        }

        //setup address structure
        memset((char *)&si_other, 0, sizeof(si_other));
        si_other.sin_family = AF_INET;
        si_other.sin_port = htons(PORT);
        si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

        //

        POINT pt;
        LPPOINT ptr = &pt;
        printf("hi %d\n", sizeof(POINT));
        int a, b;
        int *t;
        t=(int*)message;
        while (1) {
                a = ptr->x;
                b = ptr->y;
                if (!GetCursorPos(ptr)) {
                        printf("eror cursor read\n");
                }
                if ((a != ptr->x) | (b != ptr->y)) {
                        printf("%ld %ld \n", ptr->x, ptr->y);
                        t[0] = ptr->x;
                        t[1] = ptr->y;
                        if (sendto(s, message, BUFLEN, 0,
                                   (struct sockaddr *)&si_other,
                                   slen) == SOCKET_ERROR) {
                                printf("sendto() failed with error code : %d",
                                       WSAGetLastError());
                                exit(EXIT_FAILURE);
                        }

                        memset(message, '\0', BUFLEN);
                }
        }
}
