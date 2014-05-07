#include "skynet.h"

#include "socket_server.h"
//#include "socket_poll.h"

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <unistd.h>
//#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define MAX_INFO 128
// MAX_SOCKET will be 2^MAX_SOCKET_P
#define MAX_SOCKET_P 16
#define MAX_EVENT 64
#define MIN_READ_BUFFER 64
#define SOCKET_TYPE_INVALID 0
#define SOCKET_TYPE_RESERVE 1
#define SOCKET_TYPE_PLISTEN 2
#define SOCKET_TYPE_LISTEN 3
#define SOCKET_TYPE_CONNECTING 4
#define SOCKET_TYPE_CONNECTED 5
#define SOCKET_TYPE_HALFCLOSE 6
#define SOCKET_TYPE_PACCEPT 7
#define SOCKET_TYPE_BIND 8

#define MAX_SOCKET (1<<MAX_SOCKET_P)

#define PRIORITY_HIGH 0
#define PRIORITY_LOW 1

struct write_buffer {
	struct write_buffer * next;
	char *ptr;
	int sz;
	void *buffer;
};

struct wb_list {
	struct write_buffer * head;
	struct write_buffer * tail;
};

struct socket {
	int fd;
	int id;
	int type;
	int size;
	int64_t wb_size;
	uintptr_t opaque;
	struct wb_list high;
	struct wb_list low;
};

struct socket_server {
	int recvctrl_fd;
	int sendctrl_fd;
	int checkctrl;
//	poll_fd event_fd;
	int alloc_id;
	int event_n;
	int event_index;
//	struct event ev[MAX_EVENT];
	struct socket slot[MAX_SOCKET];
	char buffer[MAX_INFO];
//	fd_set rfds;
};

struct request_open {
	int id;
	int port;
	uintptr_t opaque;
	char host[1];
};

struct request_send {
	int id;
	int sz;
	char * buffer;
};

struct request_close {
	int id;
	uintptr_t opaque;
};

struct request_listen {
	int id;
	int fd;
	uintptr_t opaque;
	char host[1];
};

struct request_bind {
	int id;
	int fd;
	uintptr_t opaque;
};

struct request_start {
	int id;
	uintptr_t opaque;
};

struct request_package {
	uint8_t header[8];	// 6 bytes dummy
	union {
		char buffer[256];
		struct request_open open;
		struct request_send send;
		struct request_close close;
		struct request_listen listen;
		struct request_bind bind;
		struct request_start start;
	} u;
	uint8_t dummy[256];
};

union sockaddr_all {
//	struct sockaddr s;
//	struct sockaddr_in v4;
//	struct sockaddr_in6 v6;
};

#define MALLOC skynet_malloc
#define FREE skynet_free

static void
socket_keepalive(int fd) {
//	int keepalive = 1;
//	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive , sizeof(keepalive));  
}

static int
reserve_id(struct socket_server *ss) {
	return -1;
}

static inline void
clear_wb_list(struct wb_list *list) {
	list->head = NULL;
	list->tail = NULL;
}

struct socket_server * 
socket_server_create() {
	struct socket_server *ss = MALLOC(sizeof(*ss));
	return ss;
}

static void
free_wb_list(struct wb_list *list) {
}

static void
force_close(struct socket_server *ss, struct socket *s, struct socket_message *result) {
}

void 
socket_server_release(struct socket_server *ss) {
}

static inline void
check_wb_list(struct wb_list *s) {
	assert(s->head == NULL);
	assert(s->tail == NULL);
}

static struct socket *
new_fd(struct socket_server *ss, int id, int fd, uintptr_t opaque, bool add) {
	return NULL;
}

// return -1 when connecting
static int
open_socket(struct socket_server *ss, struct request_open * request, struct socket_message *result, bool blocking) {
	return SOCKET_ERROR;
}

static int
send_list(struct socket_server *ss, struct socket *s, struct wb_list *list, struct socket_message *result) {
	return -1;
}

static inline int
list_uncomplete(struct wb_list *s) {
	return -1;
}

static void
raise_uncomplete(struct socket * s) {
}

static int
send_buffer(struct socket_server *ss, struct socket *s, struct socket_message *result) {
	return -1;
}

static int
append_sendbuffer_(struct wb_list *s, struct request_send * request, int n) {
	return -1;
}

static inline void
append_sendbuffer(struct socket *s, struct request_send * request, int n) {
	s->wb_size += append_sendbuffer_(&s->high, request, n);
}

static inline void
append_sendbuffer_low(struct socket *s, struct request_send * request) {
	s->wb_size += append_sendbuffer_(&s->low, request, 0);
}

static inline int
send_buffer_empty(struct socket *s) {
	return (s->high.head == NULL && s->low.head == NULL);
}


static int
send_socket(struct socket_server *ss, struct request_send * request, struct socket_message *result, int priority) {
	return -1;
}

static int
listen_socket(struct socket_server *ss, struct request_listen * request, struct socket_message *result) {
	return SOCKET_ERROR;
}

static int
close_socket(struct socket_server *ss, struct request_close *request, struct socket_message *result) {
	return -1;
}

static int
bind_socket(struct socket_server *ss, struct request_bind *request, struct socket_message *result) {
	return SOCKET_OPEN;
}

static int
start_socket(struct socket_server *ss, struct request_start *request, struct socket_message *result) {
	return -1;
}

static void
block_readpipe(int pipefd, void *buffer, int sz) {
}

static int
has_cmd(struct socket_server *ss) {
	return 0;
}

// return type
static int
ctrl_cmd(struct socket_server *ss, struct socket_message *result) {
	return -1;
}

// return -1 (ignore) when error
static int
forward_message(struct socket_server *ss, struct socket *s, struct socket_message * result) {
	return SOCKET_DATA;
}

static int
report_connect(struct socket_server *ss, struct socket *s, struct socket_message *result) {
	return SOCKET_OPEN;
}

// return 0 when failed
static int
report_accept(struct socket_server *ss, struct socket *s, struct socket_message *result) {
	return 1;
}


// return type
int 
socket_server_poll(struct socket_server *ss, struct socket_message * result, int * more) {
	return -1;
}

static void
send_request(struct socket_server *ss, struct request_package *request, char type, int len) {
}

static int
open_request(struct socket_server *ss, struct request_package *req, uintptr_t opaque, const char *addr, int port) {
	return -1;
}

int 
socket_server_connect(struct socket_server *ss, uintptr_t opaque, const char * addr, int port) {
	return -1;
}

int 
socket_server_block_connect(struct socket_server *ss, uintptr_t opaque, const char * addr, int port) {
	return -1;
}

// return -1 when error
int64_t 
socket_server_send(struct socket_server *ss, int id, const void * buffer, int sz) {
	return -1;
}

void 
socket_server_send_lowpriority(struct socket_server *ss, int id, const void * buffer, int sz) {
}

void
socket_server_exit(struct socket_server *ss) {
}

void
socket_server_close(struct socket_server *ss, uintptr_t opaque, int id) {
}

static int
do_listen(const char * host, int port, int backlog) {
	return -1;
}

int 
socket_server_listen(struct socket_server *ss, uintptr_t opaque, const char * addr, int port, int backlog) {
	return -1;
}

int
socket_server_bind(struct socket_server *ss, uintptr_t opaque, int fd) {
	return -1;
}

void 
socket_server_start(struct socket_server *ss, uintptr_t opaque, int id) {
}


