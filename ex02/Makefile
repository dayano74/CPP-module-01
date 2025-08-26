NAME := brain

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	@./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re run