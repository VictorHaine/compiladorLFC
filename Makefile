
SRCDIR	= src
INCDIR	= src/include
OBJDIR	= obj
BINDIR	= bin

OUTNAME = clfc
CC 		= gcc
CFLAGS	= -std=c99 -g -Wall -I. -I$(INCDIR) -v

LINKER	= gcc -o
LFLAGS	= -Wall -g -I. -lm -v

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SOURCES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) 
HEADERS := $(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/*/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
RMCMD	:= rm -rf

compile: $(OBJECTS)
	@$(LINKER) $(BINDIR)/$(OUTNAME) $(LFLAGS) $(OBJECTS)
	@echo "Linking ok!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	echo "\nArquivo "$<" compilado com sucesso."

clean:
	@$(shell find $(OBJDIR)/ -iname "*.o" | xargs -0 /bin/rm -f)
	@$(shell find $(BINDIR)/ | xargs -0 /bin/rm -f)
	clear
	@echo "\nCompilador LFC\n"
	@echo "Limpeza realizada com sucesso!"

ls:
	@echo "Sources: $(SOURCES)"
	@echo "Headers: $(HEADERS)"
	@echo "Objects: $(OBJECTS)"

# DEPDIR = .d
# $(shell mkdir -p $(DEPDIR) >/dev/null)
# DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

# COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
# COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
# POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d


# %.o : %.c
# %.o : %.c $(DEPDIR)/%.d
# 		$(COMPILE.c) $(OUTPUT_OPTION) $<
# 		$(POSTCOMPILE)

# %.o : %.cc
# %.o : %.cc $(DEPDIR)/%.d
# 		$(COMPILE.cc) $(OUTPUT_OPTION) $<
# 		$(POSTCOMPILE)

# %.o : %.cxx
# %.o : %.cxx $(DEPDIR)/%.d
# 		$(COMPILE.cc) $(OUTPUT_OPTION) $<
# 		$(POSTCOMPILE)

# $(DEPDIR)/%.d: ;
# .PRECIOUS: $(DEPDIR)/%.d

# -include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))