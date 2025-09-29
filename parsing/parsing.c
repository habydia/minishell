#include "../include/parsing.h"



void free_cmds(t_cmd *cmds)
{
        t_cmd *temp;

        temp = cmds;

        while(temp)
        {
                 free(temp->name);
                 free_args_on_error(temp->args);
                 free_redirs(temp->redirs);
                 temp = temp->next;
        }
        free(cmds);
}

void free_redirs( t_redir *redirs)
{
        t_redir *current; 

        current = redirs;

        while(current)
        {
                free(current->file);
                current = current->next;
        }
        free(redirs);
}

void free_tokens(t_token *tokens)
{
        t_token *temp; 

        temp = tokens;
        while(temp)
        {
                free(temp->value);
                temp = temp->next;
        }
        free(tokens);
}

t_cmd   *parsing(const char *line)
{
        t_token *tokens;
        t_cmd   *cmds;

        tokens = line_lexer(line);
        if (!tokens)
                return (NULL);

        tokens = expand_tokens(tokens);
        if (!tokens)
                return (NULL);
                
        cmds = parse_tokens(tokens);
        if(!cmds)
                free_cmds(cmds);

        free_tokens(tokens);
        return (cmds);
}