#--- Directories ---#
SRCDIR	:= srcs
BSRCDIR	:= $(SRCDIR)/srcs_bonus
OBJDIR	:= objs
DEPDIR	:= $(OBJDIR)/.deps
INCDIR	:= $(shell find incs -type d)
MLXDIR	:= minilibx_opengl_20191021

VPATH	:= $(shell find $(SRCDIR) -type d)

#--- Source files ---#
BSRCS	:= $(shell find $(BSRCDIR) -type f -name \*_bonus.c)
SRCS	:= $(shell find $(SRCDIR) -type f -name \*.c ! -name \*_bonus.c)
FILTER	:= $(foreach FILE,$(notdir $(subst _bonus,,$(BSRCS))),	\
			$(shell find $(SRCDIR) -type f -name $(FILE)))
CSRCS	:= $(filter-out $(FILTER),$(SRCS))

#--- Object files ---#
OBJS	:= $(addprefix $(OBJDIR)/,$(notdir $(SRCS:%.c=%.o)))
BOBJS	:= $(addprefix $(OBJDIR)/,$(notdir $(BSRCS:%.c=%.o)))
LIBMLX	:= $(MLXDIR)/libmlx.a

NAME := cub3d

#--- Flags ---#
LDFLAGS		:=
IFLAGS		:= $(addprefix -I ,$(INCDIR)) -I $(MLXDIR)
MLXFLAGS	:= -framework OpenGL -framework AppKit
CFLAGS		:= -Wall -Wextra -Werror -O3 $(IFLAGS) -o
DEPFLAGS	 = -MT $@ -MMD -MF $(DEPDIR)/$*.tmpd

CC := gcc

#--- Compiler rules ---#
COMPILE.c	= $(CC) $(CFLAGS) $@ $(DEPFLAGS) -c
LINK.c		= $(CC) $(LDFLAGS) $(MLXFLAGS) $(CFLAGS)
POSTCOMPILE	= mv -f $(DEPDIR)/$*.tmpd $(DEPDIR)/$*.d && touch $@

#--- Other rules ---#
MKDIR	 = mkdir -p $@
RM		:= rm -rf

#-------------------------------------------------------------------------------#

$(NAME): $(OBJS) $(LIBMLX)
	$(LINK.c) $@ $^

all: $(NAME)

bonus: $(CSRCS) $(BOBJS) $(LIBMLX)
	$(LINK.c) $(NAME) $^

$(OBJDIR)/%.o : %.c $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $<
	@$(POSTCOMPILE)

$(LIBMLX):
	$(MAKE) -C $(MLXDIR)

$(DEPDIR):
	@$(MKDIR)

DEPS := $(addprefix $(DEPDIR)/,$(notdir $(SRCS:%.c=%.d)))	\
		$(addprefix $(DEPDIR)/,$(notdir $(BSRCS:%.c=%.d)))
$(DEPS):
include $(wildcard $(DEPS))

clean:
	$(RM) $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean
	@$(RM) $(NAME).dSYM

fclean: clean
	$(RM) $(NAME)

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re bonus
