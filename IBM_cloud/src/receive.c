#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/utils.h>
#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include "send.receive.h"
 
static struct ubus_context * ctx = NULL;
static struct blob_buf b;
static const char * cli_path;
 
enum
{
    SCAN_CHNID,
    SCAN_POLICY_MAX,
};
 
static const struct blobmsg_policy scan_policy[SCAN_POLICY_MAX] = {
    [SCAN_CHNID] = {.name = "chnID", .type = BLOBMSG_TYPE_INT32},
};
 
static int timeout = 30;
static bool simple_output = false;
 
static void scanreq_prog_cb(struct ubus_request *req, int type, struct blob_attr *msg)
{
    char *str;
    if (!msg)
        return;
 
    /* 
         Treated the returned message here.
         This example only prints the returned message.
    */
    str = blobmsg_format_json_indent(msg, true, simple_output ? -1 : 0);
    printf("%s\n", str);
    free(str);
}
 
static int client_ubus_call()
{
    unsigned int id;
    int ret;
 
    blob_buf_init(&b, 0);
 
    /*  Parameters that need to be passed */
    blobmsg_add_u32(&b, scan_policy[SCAN_CHNID].name, 0);
 
    /*
         Query the UBUSD inquire with "scan_prog" object,
         Returns its ID if
    */
    ret = ubus_lookup_id(ctx, "scan_prog", &id);
    if (ret != UBUS_STATUS_OK) {
        printf("lookup scan_prog failed\n");
        return ret;
    }
    else {
        printf("lookup scan_prog successs\n");
    }
    
    /*  Call the "scan" method of "scan_prog" object */
    return ubus_invoke(ctx, id, "scan", b.head, scanreq_prog_cb, NULL, timeout * 1000);
}
 
/*
 The declaration of ubus_invoke () is as follows:
int ubus_invoke(struct ubus_context *ctx, uint32_t obj, const char *method,
                struct blob_attr *msg, ubus_data_handler_t cb, void *priv, int timeout);
                
 Where the CB parameter is a message callback function, its function type is defined as:
typedef void (*ubus_data_handler_t)(struct ubus_request *req,
                    int type, struct blob_attr *msg);
 The parameter TYPE is the type of request message, such as ubus_msg_invoke, ubus_msg_data, etc.
 The parameter MSG stores the reply message obtained from the server, and the struct blob_attr type is also parsed by blobalmsg_parse ().
 The parameter REQ saves the message attribute of the requester, where the REQ-> Priv is the priv parameter in Ubus_invoke (),
 Use this parameter to pass some additional data.
*/
 
static int client_ubus_init(const char *path)
{
    uloop_init();
    cli_path = path;
 
    ctx = ubus_connect(path);
    if (!ctx)
    {
        printf("ubus connect failed\n");
        return -1;
    }
    
    printf("connected as %08x\n", ctx->local_id);
 
    return 0;
}
 
static void client_ubus_done(void)
{
    if (ctx)
        ubus_free(ctx);
}
 
int main(int argc, char * argv[])
{
    /*  Unix socket created by ubusd, the default value is "/var/run/ubus.sock" */
    char * path = NULL;
 
    /*  Connect UBUSD */
    if (UBUS_STATUS_OK != client_ubus_init(path))
    {
        printf("ubus connect failed!\n");
        return -1;
    }
 
    /*  Call a UBUS method and process the return result */
    client_ubus_call();
 
    client_ubus_done();
 
    return 0;
}