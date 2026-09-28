/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:29:40 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 10:29:43 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h> 
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../lib/libft/libft.h"
# include <stdbool.h>
# include <sys/wait.h>

# define IS_D_GREAT ">>"
# define IS_D_LESS "<<"
# define IS_PIPE "|"
# define IS_GREAT ">"
# define IS_LESS "<"
# define MAX_ARGS 256
# define DQUOTE 34
# define SQUOTE 39

# define CYAN	"\e[36m"
# define RESET	"\e[0m"
# define PURPLE "\e[0;35m"
# define YELLOW "\e[0;33m"

enum	e_type
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	ARG
};

typedef struct s_token
{
	char			*value;// Texto del token (ej: "ls", "-l", "|", ">")
	int				type;
	int				position; // Tipo de token (COMANDO, PIPE, etc.)
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv; // Argumentos del comando (ej: {"ls", "-l", NULL})
	char			*path; // path para execue
	char			**infile; // Archivo de entrada (si hay redirección "<")
	int				fd_inf;
	char			**outfile; // Archivo de salida (si hay redirección ">")
	int				fd_out;
	int				append; // Si es '>>', indica modo append
	char			**here_doc;
	bool			single_q;
	bool			double_q;
	bool			dollar;
	struct s_cmd	*prev; // Comando antes del PIPE (izquierda)
	struct s_cmd	*next; // Comando después del PIPE (derecha)
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		last_exit; // supose to be global variable
	int		num_pipes;
	bool	single_q;
	bool	double_q;
	char	*env_var;
	t_token	*tokens;
	t_cmd	*cmd_tree;
	int		fd[2]; // multiples pipex
	pid_t	*pids; // multiples pipex
	int		fd_temp; // para el H_D
	int		exit; // evitar leaks de memoria
}	t_shell;

// global
extern int	g_flag_signal;

//builtin_cd_env
void	builtin_cd(t_shell *s, char **arg);
void	builtin_env(t_shell *shelly, char **argv);
void	print_env(t_shell *shelly);

//builtins_echo
void	builtin_echo(t_cmd *current, t_shell *shelly);
char	*join_env(char **argv, char *path, t_shell *shelly);

//builtins_export
void	builtin_export(char **argv, t_shell *shelly, int i, int flag);

//builtins_unset
void	builtin_unset(t_shell *shelly, char **argv, int i);
void	check_if_free(char *to_search);

// builtins exit pwd
void	builtin_exit(t_shell *shelly, char **argv);
void	builtin_pwd(t_shell *shelly);

//builtins_utils
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen_double(char **argv);
void	update_env(t_shell *shell, char *new_line, size_t index, size_t i);
void	search_env_var(t_shell *shelly, char *to_search, char *home, int i);

// choose_fork_utils
void	check_builtin_in_fork(t_shell *shelly, char **argv);
void	choose_fork_aux(t_shell *shelly, int i);

// choose fork
int		choose_fork(t_shell *shelly, int child, int fd_prev);

//handle_redirections
t_cmd	*create_new_cmd(t_shell *shelly);
t_cmd	*handle_pipe(t_shell *shelly, t_cmd *current);
int		*handle_redirections(t_token **tmp, t_cmd *current, int *index);

//convert_cmd
t_cmd	*convert_tokens_to_cmd(t_shell *shelly);

//expander_utils
char	*append_variable(char *result, char *input, int *i, t_shell *shelly);
char	*append_char(char *result, char c);
char	*strjoin_and_free(char *s1, char *s2);

//expander
//char	*expand_line(char *input, t_shell *shelly,
//			int in_squote, int in_dquote);
//int		is_quote(char c);
//int		is_valid_var_char(char c, int pos);
//char	*extract_var_name(char *str, int *i, int pos);
char	*expand_var(char *str, int *i, t_shell *shelly);

//expander_str
char	*ft_strndup(const char *s, size_t n);
char	*parse_expansion(char *input, t_shell *shelly);

// fork_execution
void	first_fork_b(t_shell *shelly, t_cmd *cmd);
void	middle_fork(t_shell *shelly, t_cmd *cmd, int fd_prev);
void	last_fork(t_shell *shelly, t_cmd *cmd, int fd_prev);

//free
//void	free_cmd(t_cmd *cmds);
//void	free_tokens(t_token *tokens);
void	free_split(char **split);
void	reset_up(t_shell *shelly);
void	free_env_var(t_shell *shelly);

//ft_split_up
char	**ft_split_up(t_shell *shelly, const char *s);

//open files
void	create_all_files(t_shell *s, t_cmd *c);
void	open_files(t_shell *shelly, t_cmd *c);

//join cmd built
int		is_builtin(char *cmd);
//void	open_files(t_cmd *current);
void	update_shlvl(t_shell *shelly);
void	check_built_comand(t_shell *s);

//minishell
void	init_shell(t_shell *shelly, char **env);
void	execute_builtin(t_cmd *cmd, t_shell *shelly, char *cc);
//void	execute_command(char *input, t_shell *shelly);
void	prompt_loop(t_shell *shelly);

//lexer
void	init_token(char **tokens, t_shell *shelly);
//void	add_token(char *str, int type, t_token **tokens, int position);
bool	wrong_pipe(t_shell *shelly, char *input);
int		is_not_empty_or_spaces(char *str);

// set up heredoc
void	create_file(t_cmd *cmd, t_shell *s);

// set up pipe
int		setup_pipe(t_shell *shelly);

//signals
//void	signal_handler(int sig);
void	handle_signals(void);

//utils
bool	check_quotation(char *str, t_shell *t_shelly);
t_token	*find_last_node(t_token	*list);
//void	print_tokens(t_token *tokens);
//void	print_cmd(t_cmd *cmds);
//void	print_split(char **args);
void	check_direction(t_cmd *current, int type);
int		num_pipex(t_shell *shelly);
char	*aux_path(char **split1, char **split2, char *join, char *join_cmd);
//void	safe_print(const char *str);

//reset
//void	ft_error(t_shell *shelly, char *str, int num_exit);
void	ft_error(t_shell *shelly, char *str, int num_exit, char *var);
void	free_shell(t_shell *shelly);

#endif
