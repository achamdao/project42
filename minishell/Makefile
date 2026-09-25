CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
INCDIR = header
HEADERS := \
	$(INCDIR)/minishell.h \
	$(INCDIR)/builtins.h \
	$(INCDIR)/lexer.h \
	$(INCDIR)/cwd_utils.h \
	$(INCDIR)/env_utils.h \
	$(INCDIR)/redir.h \
	$(INCDIR)/init_cmd.h \
	$(INCDIR)/exec_pipeline.h \
	$(INCDIR)/here_doc.h \
	$(INCDIR)/file_utils.h \
	$(INCDIR)/types.h \
	$(INCDIR)/utils.h \
	$(INCDIR)/start.h \

LBFT = lbft/libft.a
SRCS = Main/Flash_Bash.c Main/start_minishell.c src/excution/exec_pipeline.c src/excution/exec_single_cmd.c src/excution/init_cmd.c src/excution/parse_cmd.c src/excution/start.c \
		src/redirections/generate_string.c src/redirections/here_doc.c src/redirections/hindle_fd.c src/redirections/redirections.c src/excution/pipes.c\
		src/utilis/check_fiale.c src/utilis/pop.c src/utilis/cleanup.c src/utilis/count.c src/utilis/error.c src/utilis/free_allocation.c src/utilis/pipes.c src/utilis/stack_utils.c src/utilis/stack.c src/utilis/utilis_var.c src/utilis/utilis.c src/utilis/var.c \
		src/ft_strndup.c src/utilis/open.c src/excution/array_cmd_utils.c src/excution/heredoc_signal_utils.c src/excution/exec_single_utlis.c src/redirections/redirection_utilis.c src/redirections/utilis_here_doc.c\
building_cmd/utilis.c \
building_cmd/cd/cd_utilis2.c building_cmd/cd/cd_utils1.c building_cmd/cd/cd.c\
building_cmd/echo.c \
building_cmd/env/env.c building_cmd/env/full_stack_env.c building_cmd/env/env_utils.c\
building_cmd/exit/bash_atoi_utils.c building_cmd/exit/exit.c\
building_cmd/export/env_sorting.c building_cmd/export/export_command.c building_cmd/export/utilis.c building_cmd/export/value_processing.c building_cmd/export/var_checks.c\
building_cmd/pwd.c \
building_cmd/unset.c \
building_cmd/getcwd/cwd_helpers.c building_cmd/getcwd/getcwd.c building_cmd/getcwd/path_building.c building_cmd/getcwd/path_utils.c\

PARSE_SRCS = parse/get_clean_path.c parse/lexer.c parse/stack_Data_structur.c parse/check_valid_quote.c tokenization/check_valid_prompt.c parse/utilis_function.c\
tokenization/check_valid_redirection.c tokenization/name_of_word.c tokenization/print_error.c tokenization/tokenization_names.c tokenization/process_cleaner_stack.c tokenization/utilise_function.c\
tokenization/cleaner_stack.c tokenization/handel_redirection.c tokenization/handle_her_doc.c tokenization/parsing_redirection.c\
tokenization/override_var.c tokenization/component_stack_files.c parse/handle_signal.c tokenization/process_stored_file.c tokenization/process_syntax_error.c\
tokenization/fix_empty_pipe_line.c tokenization/empty_command_fix.c tokenization/component_stack_cleaner.c Main/init_env.c tokenization/process_her_doc.c\

OBJS = $(SRCS:.c=.o)
OBJS_PARS = $(PARSE_SRCS:.c=.o)


all : lbftm $(NAME)

$(NAME) : $(OBJS) $(LBFT) $(OBJS_PARS)
	$(CC) $(FLAGS)  $(LBFT) -lreadline $^ -L/mnt/homes/mjaouchi/.brew/opt/readline/lib -ltermcap -o $@

lbftm:
	make -C lbft

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -I/mnt/homes/mjaouchi/.brew/opt/readline/include -o $@

clean:
	rm -rf $(OBJS) $(OBJS_PARS)
	make -C lbft clean
fclean : clean
	rm -rf $(NAME)
	make -C lbft fclean
re : fclean all
PHONY : clean

