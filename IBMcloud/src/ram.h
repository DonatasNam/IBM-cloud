#include <libubox/blobmsg_json.h>
#include <libubus.h>


struct ubus_context *ctx;
struct ubus_request_data*rq;
enum {
	TOTAL_MEMORY,
	FREE_MEMORY,
	SHARED_MEMORY,
	BUFFERED_MEMORY,
	__MEMORY_MAX,
};

enum {
	MEMORY_DATA,
	__INFO_MAX,
};

void board_cb(struct ubus_request *req, int type, struct blob_attr *msg);
static const struct blobmsg_policy memory_policy[__MEMORY_MAX];
extern int rc;
