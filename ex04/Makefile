NAME := replace

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRCDIR := srcs
INCDIR := incs
OBJDIR := objs
DEPDIR := deps

SRCS := main.cpp FileReplacer.cpp

SRCS := $(addprefix $(SRCDIR)/,$(SRCS))
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)

CXXFLAGS += -I$(INCDIR)

RM := rm -f
RMDIR := rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)
	$(RMDIR) $(OBJDIR) $(DEPDIR)

re: fclean all

run: $(NAME)
	@./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re

