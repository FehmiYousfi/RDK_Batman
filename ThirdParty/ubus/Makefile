include rules.mk

CFLAGS = -I$(INCDIR) -I$(INCDIR_ubox) -I$(INCDIR_ubus) -I$(INCDIR_json) -fPIC
CFLAGS_NO_IMPLICIT_FUNCTION_DECLARATION = $(filter-out -Wimplicit-function-declaration, $(CFLAGS))
all: check_dirs generate_targets export_library

check_dirs:
	$(call check_and_create_dir,$(OUT_LIB_dir))
	$(call check_and_create_dir,$(BUILDDIR))
	$(call check_and_create_dir,$(BINDIR))
	$(call check_and_create_dir,$(combined_out_dir))

generate_targets : $(EXECUTABLES)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CFLAGS_NO_IMPLICIT_FUNCTION_DECLARATION) -c $< -o $@
$(BUILDDIR)/%.o: $(INCDIR_ubus)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CFLAGS_NO_IMPLICIT_FUNCTION_DECLARATION) -c $< -o $@
$(BUILDDIR)/%.o: $(INCDIR_ubox)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CFLAGS_NO_IMPLICIT_FUNCTION_DECLARATION) -c $< -o $@
$(BUILDDIR)/%.o: $(INCDIR_json)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CFLAGS_NO_IMPLICIT_FUNCTION_DECLARATION) -c $< -o $@

$(BINDIR)/client: $(BUILDDIR)/client.o $(filter-out $(BUILDDIR)/server.o $(BUILDDIR)/jshn.o $(BUILDDIR)/blobmsg_json.o, $(OBJECTS))
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CFLAGS_NO_IMPLICIT_FUNCTION_DECLARATION) $^ -o $@ 

$(BINDIR)/server: $(BUILDDIR)/server.o $(filter-out $(BUILDDIR)/client.o $(BUILDDIR)/jshn.o $(BUILDDIR)/blobmsg_json.o, $(OBJECTS))
	@mkdir -p $(@D)
	$(CC) $^ -o $@ 
	
export_library:
	@echo "\n"
	@mkdir -p $(OUT_LIB_dir)
	ld -r -o $(combined_out_dir)/libcu_ubus.o $(filter-out $(BUILDDIR)/client.o $(BUILDDIR)/server.o ,$(object_ubus))
	ar rcs $(OUT_LIB_dir)/libcu_ubus.a $(combined_out_dir)/libcu_ubus.o
	$(CC) -shared -o $(OUT_LIB_dir)/libcu_ubus.so $(filter-out $(BUILDDIR)/client.o $(BUILDDIR)/server.o ,$(object_ubus))
	ld -r -o $(combined_out_dir)/libcu_ubox.o $(filter-out $(BUILDDIR)/jshn.o $(BUILDDIR)/blobmsg_json.o , $(object_ubox))
	ar rcs $(OUT_LIB_dir)/libcu_ubox.a $(combined_out_dir)/libcu_ubox.o
	$(CC) -shared -o $(OUT_LIB_dir)/libcu_ubox.so $(filter-out $(BUILDDIR)/jshn.o $(BUILDDIR)/blobmsg_json.o , $(object_ubox))
	ld -r -o $(combined_out_dir)/libcu_json.o $(object_json)
	ar rcs $(OUT_LIB_dir)/libcu_json.a $(combined_out_dir)/libcu_json.o
	$(CC) -shared -o $(OUT_LIB_dir)/libcu_json.so $(object_json)
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(OUT_LIB_dir)

.PHONY: all clean


