CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUFFER = -D BUFFER_SIZE=42

# Standard version
NAME = test_gnl
SRC = test_gnl.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# Bonus version
NAME_BONUS = test_gnl_bonus
SRC_BONUS = test_gnl.c get_next_line_bonus.c get_next_line_utils_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(BUFFER) -o $(NAME) $(OBJ)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(BUFFER) -o $(NAME_BONUS) $(OBJ_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(BUFFER) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)
	@rm -f test*.txt
	@rm -f *.bin
	@rm -f empty.txt
	@rm -f one_line_no_nl.txt
	@rm -f one_line_nl.txt
	@rm -f multiple_lines.txt
	@rm -f large_file.txt
	@rm -f binary.bin
	@rm -f buffer_test.txt
	@rm -f buffer_test1.txt
	@rm -f buffer_test2.txt
	@rm -f close_test.txt
	@rm -f interleaved_*.txt
	@rm -f interleaved_*.bin
	
fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

test: all
	./$(NAME)
	./$(NAME_BONUS)

test1: all
	./$(NAME)

test2: all
	./$(NAME_BONUS)

# Test with different buffer sizes
test_buffer1: fclean
	$(CC) $(CFLAGS) -D BUFFER_SIZE=1 -o $(NAME) $(SRC)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=1 -o $(NAME_BONUS) $(SRC_BONUS)
	./$(NAME)
	./$(NAME_BONUS)

test_buffer42: fclean
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 -o $(NAME) $(SRC)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 -o $(NAME_BONUS) $(SRC_BONUS)
	./$(NAME)
	./$(NAME_BONUS)

test_buffer9999: fclean
	$(CC) $(CFLAGS) -D BUFFER_SIZE=9999 -o $(NAME) $(SRC)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=9999 -o $(NAME_BONUS) $(SRC_BONUS)
	./$(NAME)
	./$(NAME_BONUS)

.PHONY: all clean fclean re test test1 test2 test_buffer1 test_buffer42 test_buffer9999
