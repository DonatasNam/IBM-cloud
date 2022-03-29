#include <libubox/blobmsg_json.h>
#include <libubus.h>
#include <sys/sysinfo.h>



static int ram_info(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg);

enum{
	RAM_VALUE,
	RAM_VALUE_MAX
};

static const struct blobmsg_policy ram_policy[] = {
	[RAM_VALUE] = { .name = "ram_value", .type = BLOBMSG_TYPE_INT32 },
};

static const struct ubus_method ram_methods[] = {
    UBUS_METHOD("ram", ram_info, ram_policy)
};

static struct ubus_object_type ram_object_type = UBUS_OBJECT_TYPE("ram", ram_methods);

static struct ubus_object ram_object = {
	.name = "ram",
	.type = &ram_object_type,
	.methods = ram_methods,
	.n_methods = ARRAY_SIZE(ram_methods),
};
