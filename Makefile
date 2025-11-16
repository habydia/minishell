CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g3 -MMD -MP

UNAME_S := $(shell uname -s)

SRC = parsing/lexer/operator_handler.c \
      parsing/lexer/tokenizer.c \
	  parsing/lexer/tokenizer_handler.c \
	  parsing/lexer/quotes_utils.c\
	  parsing/lexer/ft_free.c \
      parsing/parser/command_builder.c \
	  parsing/parser/expander.c \
	  parsing/parser/expander_utils.c \
      parsing/parser/pipeline_handler.c \
      parsing/parser/redirect_handler.c \
	  parsing/parser/heredoc_handler.c \
	  parsing/parser/command_builder_utils.c \
	  parsing/syntax_checker.c \
	  parsing/parsing.c \
	  signal/heredoc_signals.c \
	  signal/reader.c \
	  signal/signals.c \
	  exec/apply_redirections_exec.c \
	  exec/exec_utils.c \
	  exec/exec.c \
	  exec/get_path_exec.c \
	  exec/get_path_handle_access_cmd_exec.c \
	  exec/get_path_utils_exec.c \
	  exec/handle_child_process_exec.c \
	  exec/handle_parent_builtins_exec.c \
	  exec/handle_parent_process.c \
	  exec/update_envp_exec_utils.c \
	  exec/update_envp_exec.c \
	  env/free_all.c \
	  env/init_data_structure.c \
	  env/init_envp_array.c \
	  env/init_lst_env_utils.c \
	  env/init_lst_env.c \
	  builtins/exec_builtins.c \
	  builtins/ft_cd_utils.c \
	  builtins/ft_cd.c \
	  builtins/ft_echo.c \
	  builtins/ft_env.c \
	  builtins/ft_exit_is_number_utils.c \
	  builtins/ft_exit.c \
	  builtins/ft_export_utils_key.c \
	  builtins/ft_export_utils.c \
	  builtins/ft_export.c \
	  builtins/ft_pwd.c \
	  builtins/ft_unset.c \
	  main.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
NAME = minishell

all: $(NAME)

LIB_DIR = libft/
LIBFT = $(LIB_DIR)/libft.a

-include $(OBJ:.o=.d)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -lft $(LDFLAGS) -lreadline -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/parsing/lexer
	mkdir -p $(OBJ_DIR)/parsing/parser
	mkdir -p $(OBJ_DIR)/signal
	mkdir -p $(OBJ_DIR)/exec
	mkdir -p $(OBJ_DIR)/env
	mkdir -p $(OBJ_DIR)/builtins

$(LIBFT): force
	$(MAKE) -C $(LIB_DIR) bonus
	
force:

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(HEADER) Makefile | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug fdebug
