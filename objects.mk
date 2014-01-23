objs += $(APP)thundercat.o
objs += $(APP)testcase.o


$(objs): MODULE_NAME="ThunderCat"
$(objs): CFLAGS += -I $(APP_DIR)include
$(objs): CFLAGS += -mthumb -mthumb-interwork

