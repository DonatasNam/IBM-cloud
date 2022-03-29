#include "ram.h"

static int ram_info(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
	time_t now;
	struct tm *tm;

	struct blob_buf b = {};

	struct sysinfo info;
	void *c;
	char line[256];
	char *key, *val;
	unsigned long long available, cached;
	FILE *f;

	if (sysinfo(&info))
		return UBUS_STATUS_UNKNOWN_ERROR;

	if ((f = fopen("/proc/meminfo", "r")) == NULL)
		return UBUS_STATUS_UNKNOWN_ERROR;

	available = 0;
	cached = 0;

	while (fgets(line, sizeof(line), f))
	{
		key = strtok(line, " :");
		val = strtok(NULL, " ");

		if (!key || !val)
			continue;

		if (!strcasecmp(key, "MemAvailable"))
			available = 1024 * atoll(val);
		else if (!strcasecmp(key, "Cached"))
			cached = 1024 * atoll(val);
	}

	fclose(f);

	c = blobmsg_open_array(&b, "load");
	blobmsg_add_u32(&b, NULL, info.loads[0]);
	blobmsg_add_u32(&b, NULL, info.loads[1]);
	blobmsg_add_u32(&b, NULL, info.loads[2]);
	blobmsg_close_array(&b, c);

	c = blobmsg_open_table(&b, "memory");
	blobmsg_add_u64(&b, "total",
			(uint64_t)info.mem_unit * (uint64_t)info.totalram);
	blobmsg_add_u64(&b, "free",
			(uint64_t)info.mem_unit * (uint64_t)info.freeram);
	blobmsg_add_u64(&b, "shared",
			(uint64_t)info.mem_unit * (uint64_t)info.sharedram);
	blobmsg_add_u64(&b, "buffered",
			(uint64_t)info.mem_unit * (uint64_t)info.bufferram);
	blobmsg_add_u64(&b, "available", available);
	blobmsg_add_u64(&b, "cached", cached);
	blobmsg_close_table(&b, c);

	ubus_send_reply(ctx, req, b.head);

	return UBUS_STATUS_OK;
}