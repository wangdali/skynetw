#ifndef poll_socket_iocp_h
#define poll_socket_iocp_h


static bool 
sp_invalid(int efd) {
	return efd == -1;
}

static int
sp_create() {
	return 0;
}

static void
sp_release(int efd) {
}

static int 
sp_add(int efd, int sock, void *ud) {
	return 0;
}

static void 
sp_del(int efd, int sock) {
}

static void 
sp_write(int efd, int sock, void *ud, bool enable) {
}

static int 
sp_wait(int efd, struct event *e, int max) {
	return 0;
}

static void
sp_nonblocking(int fd) {
}

#endif
