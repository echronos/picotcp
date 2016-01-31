#include "httpd.h"
#include "pico_socket.h"
#include "rtos-rigel.h"

void task_two(void);
static void receive_request_on_socket(struct pico_socket *s);
static void send_response_on_socket(struct pico_socket *s);

static int do_send = 0;
static struct pico_socket *recv_socket, *send_socket;

void task_two(void)
{
    rtos_timer_signal_set(RTOS_TIMER_ID_ONE, RTOS_TASK_ID_TWO, RTOS_SIGNAL_SET_ONE);
    rtos_timer_reload_set(RTOS_TIMER_ID_ONE, 100);
    rtos_timer_enable(RTOS_TIMER_ID_ONE);

    for (;;) {
        const RtosSignalSet signals = rtos_signal_wait_set(RTOS_SIGNAL_SET_ONE | RTOS_SIGNAL_SET_TWO | RTOS_SIGNAL_SET_THREE);
        if (signals & RTOS_SIGNAL_SET_ONE) {
            printf("task two checking in\n");
        }
        if (signals & RTOS_SIGNAL_SET_TWO) {
            receive_request_on_socket(recv_socket);
        }
        if (signals & RTOS_SIGNAL_SET_THREE) {
            send_response_on_socket(send_socket);
        }
    }
}

static void receive_request_on_socket(struct pico_socket *const s)
{
    uint8_t bfr[128];
    int ret = pico_socket_recv(s, bfr, sizeof(bfr) - 1);
    if (ret >= 0) {
        printf("---------\n");
        bfr[ret] = '\0';
        printf("%s", (char*)bfr);
        printf("---------\n");
        do_send = 1;
    } else {
        printf("Socket error occurred: %s\n", strerror(pico_err));
    }
}

static void send_response_on_socket(struct pico_socket *const s)
{
    if (do_send) {
        const char rsp[] = "HTTP/1.1 200 OK\n\
Content-Type: text/html\n\
Connection: Closed\n\
\n\
Hello, World!\n\n";
        char bfr[128];
        char *cur = bfr;
        char *end = bfr + sizeof(rsp);
        int w;

        memcpy(bfr, rsp, sizeof(rsp));

        do {
            w = pico_socket_write(send_socket, cur, end - cur);
            if (w > 0) {
                cur += w;
            } else {
                printf("Socket error occurred: %s\n", strerror(pico_err));
            }
        } while ((w > 0) && (cur < end));

        pico_socket_shutdown(send_socket, PICO_SHUT_WR);
        do_send = 0;
    }
}

void httpd_handle_request(struct pico_socket *const s) {
    recv_socket = s;
    rtos_signal_send(RTOS_TASK_ID_TWO, RTOS_SIGNAL_ID_TWO);
}

void httpd_provide_response(struct pico_socket *const s) {
    send_socket = s;
    rtos_signal_send(RTOS_TASK_ID_TWO, RTOS_SIGNAL_ID_THREE);
}
