//#include "deamon.h"

#include "ram.h"
#include <iotp_device.h>

int main(int argc, char* argv[]){
    blob_attr* msg;
    IoTPConfig *config = NULL;
    IoTPDevice *device = NULL;

    uint32_t id;
	int rc = IOTPRC_SUCCESS;

    //deamon_init();
    
   
    
    rc = IoTPConfig_create(&config, "/etc/config/ibm_conf.yaml");
        printf("\n err1: %s", IOTPRC_toString(rc));
    	if ( rc == IOTPRC_SUCCESS ) {
        	rc = IoTPDevice_create(&device,config);
                printf("\n err2: %s", IOTPRC_toString(rc));
        		if ( rc == IOTPRC_SUCCESS ) {

            		rc = IoTPDevice_connect(device);
                    printf("\n err3: %s", IOTPRC_toString(rc));
        		}
    		}
    	if ( rc != IOTPRC_SUCCESS ) { 
			exit(1);
	}
    
    ctx = ubus_connect(NULL);
		if (!ctx) {
		    printf("\n Failed to connect to ubus\n");
		    return -1;
	}
    
    while(1){
        
        rc= ubus_lookup_id(ctx, "system", &id);
        printf("\n \n err code1: %i",rc);
        
		rc= ubus_invoke(ctx, id, "info", message, board_cb, NULL, 3000);
        printf("err code2: %i",rc);
        printf("\n %s \n",message->data);

        rc = IoTPDevice_sendEvent(device,"Ram_data", message->data, "json",QoS0, NULL);
        printf("\n err5: %s", IOTPRC_toString(rc));

        sleep(10);

    }


    rc = IoTPDevice_disconnect(device);
        printf("\n err: %s", IOTPRC_toString(rc));
        if ( rc == IOTPRC_SUCCESS){
            rc = IoTPDevice_destroy(device);
                printf("\n err: %s", IOTPRC_toString(rc));
            if ( rc == IOTPRC_SUCCESS){
                rc = IoTPConfig_clear(config);
                printf("\n err: %s", IOTPRC_toString(rc));
            }
        }
        if ( rc != IOTPRC_SUCCESS ) {
            exit(1);
    }

    ubus_free(ctx);

}