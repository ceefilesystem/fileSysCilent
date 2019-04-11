#include "uvClient.h"
#include <iostream>

typedef struct write_req_t {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

/* tcp callbacks */
static void on_close_cb(uv_handle_t *);
static void on_shutdown_cb(uv_shutdown_t *, int);
static void on_alloc_cb(uv_handle_t*, size_t, uv_buf_t*);
static void on_read_cb(uv_stream_t*, ssize_t, const uv_buf_t*);
static void on_write_cb(uv_write_t*, int);
static void on_thread_cb(void*);
static void on_connect_cb(uv_connect_t*, int);

static void on_close_cb(uv_handle_t* peer)
{
	free(peer);
}

static void on_shutdown_cb(uv_shutdown_t* req, int status)
{
	uv_close((uv_handle_t*)req->handle, on_close_cb);
	free(req);
}

static void on_alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	buf->base = (char*)malloc(suggested_size);
	buf->len = suggested_size;
}

static void on_read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
	uv_shutdown_t* sreq;

	if (nread < 0) {
		if (nread == UV_EOF) {
			std::cout << "服务器主动断开\n";
		}
		else if (nread == UV_ECONNRESET) {
			std::cout << "服务器异常断开\n";
		}
		else {
			std::cout << "服务器异常断开\n";
		}

		free(buf->base);
		sreq = (uv_shutdown_t*)malloc(sizeof* sreq);
		ASSERT(0 == uv_shutdown(sreq, handle, on_shutdown_cb));
		return;
	}

	if (nread == 0) {
		free(buf->base);
		return;
	}

	if (nread > 0) {
		int ret = 0;

		uvClient* uc = (uvClient*)(handle->data);
		readCallBack callBacke = uc->getReadCallBack();
		ret = callBacke(buf->base, nread);
	}

	free(buf->base);
	return;
}

static void on_write_cb(uv_write_t* req, int status)
{
	write_req_t* wr;
	/* Free the read/write buffer and the request */
	wr = (write_req_t*)req;
	//free(wr->buf.base);
	free(wr);

	if (status == 0)
		return;

	throw (uv_strerror(status));
}

static void on_connect_cb(uv_connect_t* conn, int status)
{
	if (status == 0) {
		int r;

		r = uv_read_start(conn->handle, on_alloc_cb, on_read_cb);
		if (r) {
			throw std::exception(uv_strerror(r));
			return;
		}
	}else {
		throw std::exception(uv_strerror(status));
	}
	
	return;
}

static void on_thread_cb(void * arg)
{
	uvClient* uc = nullptr;
	if (arg)
		uc = (uvClient*)arg;

	struct sockaddr_in addr;
	int r;

	r = uv_ip4_addr(uc->ip, uc->port, &addr);
	ASSERT(r == 0);

	r = uv_tcp_connect(&uc->connectReq, &uc->tcpConn, (const struct sockaddr*) &addr, on_connect_cb);
	ASSERT(r == 0);

	r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	ASSERT(r == 0);
}

uvClient::uvClient()
{
	uv_os_setenv("UV_THREADPOOL_SIZE", "120");
	this->loop = uv_default_loop();
	const char* ip = nullptr;
	this->connectReq.data = this;
}

uvClient::~uvClient()
{
	if (this->loop)
		uv_loop_close(loop);
}

void uvClient::setReadCallBack(readCallBack rCallBack)
{
	this->rCallBack = rCallBack;
}

readCallBack uvClient::getReadCallBack()
{
	return this->rCallBack;
}

void uvClient::connectIpv4(const char* ip, int port)
{
	this->ip = ip;
	this->port = port;

	int r;
	r = uv_tcp_init(loop, &tcpConn);
	if (r) {
		throw std::exception("Socket creation error");
		return;
	}

	tcpConn.data = this;
	r = uv_thread_create(&connectThr, on_thread_cb, this);
	if (r) {
		throw std::exception("uv_thread_create() error");
		return;
	}
	
	Sleep(1000);
}

int uvClient::sendData(void * in, int len)
{
	write_req_t* wr = (write_req_t*)malloc(sizeof *wr);
	ASSERT(wr != NULL);

	wr->buf = uv_buf_init((char*)in, len == strlen((char*)in) + 1 ? len : strlen((char*)in) + 1);

	int r = uv_write(&wr->req, (uv_stream_t*)&tcpConn, &wr->buf, 1, on_write_cb);
	if (r) {
		throw std::exception(uv_strerror(r));
		return 1;
	}
	
	return 0;
}
