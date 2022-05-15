SRCS_BONUS = main.c\
			launch.c \
			init.c \
			function.c \
			time_function.c

OBJS_bonus = $(SRCS_BONUS:.c=.o)


BONUS = philo_bonus

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -lpthread

HEADER_BONUS = philo.h




all:	$(BONUS)

.PHONY:	clean fclean re bonus bench bclean

bonus: $(OBJS_bonus)
	$(CLANG) $(INCLUDE) $(FLAGS) -o $(BONUS) $(OBJS_bonus)

clean:
	rm -f $(OBJS) $(OBJS_bonus)

fclean: clean
	rm -f $(BONUS)

re: fclean all

%.o: %.c $(HEADER_BONUS)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)


