#include "ram.h"

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
	[TOTAL_MEMORY] = { .name = "total", .type = BLOBMSG_TYPE_INT64 },
	[FREE_MEMORY] = { .name = "free", .type = BLOBMSG_TYPE_INT64 },
	[SHARED_MEMORY] = { .name = "shared", .type = BLOBMSG_TYPE_INT64 },
	[BUFFERED_MEMORY] = { .name = "buffered", .type = BLOBMSG_TYPE_INT64 },
};

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
	[MEMORY_DATA] = { .name = "memory", .type = BLOBMSG_TYPE_TABLE },
};


void board_cb(struct ubus_request *req, int type, struct blob_attr *msg) {

	struct blob_buf b;
	int rc = 0;
	struct blob_attr *tb[__INFO_MAX];
	struct blob_attr *memory[__MEMORY_MAX];

	blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg), blob_len(msg));

	if (!tb[MEMORY_DATA]) {
		fprintf(stderr, "No memory data received\n");
		rc=-1;
		return;
	}

	rc =blobmsg_parse(memory_policy, __MEMORY_MAX, memory, blobmsg_data(tb[MEMORY_DATA]), blobmsg_data_len(tb[MEMORY_DATA]));
	printf("\n \n err code3: %i",rc);
	char  arr[100];
    char  arr1[100];
    char  arr2[100];
    char  arr3[100];

	sprintf(arr,"\nTotal memory -> %lld\n", blobmsg_get_u64(memory[TOTAL_MEMORY]));
	sprintf(arr1,"Free memory -> %lld\n", blobmsg_get_u64(memory[FREE_MEMORY]));
	sprintf(arr2,"Shared memory -> %lld\n", blobmsg_get_u64(memory[SHARED_MEMORY]));
	sprintf(arr3,"Buffered memory -> %lld\n", blobmsg_get_u64(memory[BUFFERED_MEMORY]));

	
	char* dat= strcat(arr,arr1);
    char* dat1= strcat(arr2,arr3);
    char* data= strcat(dat,dat1);
	
	sprintf(msg->data,"%s",data);
}



 
