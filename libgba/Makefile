.SUFFIXES:

BUILD	:=	build
SOURCES	:=	src

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS	:=	-g -O3 -Wall -Wno-switch -Wno-multichar -mthumb -mthumb-interwork -I$(INCLUDE)
AFLAGS	:=	-g -Wa,--warn -mthumb -mthumb-interwork

#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path in windows
#---------------------------------------------------------------------------------
export PATH		:=	/c/devkitARM_r6a/bin:/bin


#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))

export TARGET	:=	$(CURDIR)/lib/libgba.a

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

PREFIX	:=	arm-elf-

export CC		:=	$(PREFIX)gcc
export AS		:=	$(PREFIX)as
export LD		:=	$(PREFIX)gcc
export AR		:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

CFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export OFILES	:=	$(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(CURDIR)/include

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile


clean:
	@echo clean ...
	@rm -fr $(BUILD)


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
$(TARGET): $(OFILES)

#---------------------------------------------------------------------------------
%.a: $(OFILES)
	@echo $@
	@$(AR) rcs $@ $(OFILES)


#---------------------------------------------------------------------------------
%.o: %.c
	@echo $<
	@$(CC) -MMD $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------------------------
%.o: %.s
	@echo $<
	@$(CC) -MMD $(AFLAGS) -c $< -o$@

-include $(DEPENDS)

endif
#---------------------------------------------------------------------------------
