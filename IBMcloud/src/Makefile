SRC:= ram.c main.c deamon.c 

LDFLAGS:= -lblobmsg_json -lubox -lubus -liotp-as-device -lpaho-mqtt3as
.PHONY:all clean

all:IBMcloud

IBMcloud: $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf IBMcloud