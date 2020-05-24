NAME    = reed
MODEL   = cmm
PROPGCC = /opt/parallax
SIMPLE  = /home/lili/Documents/SimpleIDE/Learn/Simple\ Libraries

BIN = /home/lili/bin/SimpleIDE-1.1.1/parallax/bin
OBJECTS=reed.c
#CC = $(BIN)/propeller-elf-gcc
CC = $(PROPGCC)/bin/propeller-elf-gcc

# includes
INCLUDE = $(PROPGCC)/propeller-elf/include
TOOLINC = $(SIMPLE)/Utility/libsimpletools
TEXTINC = $(SIMPLE)/TextDevices/libsimpletext
I2CINC  = $(SIMPLE)/Protocol/libsimplei2c


# Libs
I2CLIB  = $(SIMPLE)/Protocol/libsimplei2c/$(MODEL)
LIB     = $(PROPGCC)propeller-elf/lib
TOOLLIB = $(SIMPLE)/Utility/libsimpletools/$(MODEL)
TEXTLIB = $(SIMPLE)/TextDevices/libsimpletext/$(MODEL)

# Loader
#LOAD=$(BIN)/propeller-load
LOAD=$(PROPGCC)/bin/propeller-load

CFLAGS  = 	-Wall -Os -m32bit-doubles -m$(MODEL) -fexceptions \
			-ffunction-sections -fdata-sections -Wl,--gc-sections -std=c99 \
			-I . -I$(INCLUDE) -I$(TOOLINC) -I$(TEXTINC) -I$(I2CINC) \
	    	-L . -L$(TOOLLIB) -L$(LIB) -L$(TEXTLIB)  -L$(I2CLIB)

LDFLAGS = -lm -lsimpletools -lsimpletext 


$(NAME): $(OBJECTS)
	mkdir -p $(MODEL)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(MODEL)/$@.elf $(LDFLAGS)

all:$(NAME)

.PHONY: all clean ram


# load to the board 
BOARD = quickstart
PORT  = /dev/ttyUSB0

ram: $(NAME)
	${LOAD} -b ${BOARD} -I $(PROPGCC)/propeller-load/ -Dreset=dtr -p ${PORT}  -r $(MODEL)/$^.elf

term: $(NAME)
	${LOAD} -b ${BOARD} -Dreset=dtr -p ${PORT} -t -r $(MODEL)/$^.elf

eeprom: $(NAME)
	${LOAD} -b ${BOARD} -I $(PROPGCC)/propeller-load/ -Dreset=dtr -p ${PORT} -e -r $(MODEL)/$^.elf
clean:
	rm -f $(MODEL)/*.elf


