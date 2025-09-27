#include "../include/parsing.h"

t_cmd   *parsing(const char *line)
{
        t_token *tokens;
        t_cmd   *cmds;

        tokens = line_lexer(line);
        if (!tokens)
                return (NULL);
        cmds = parse_tokens(tokens);
        free_tokens(tokens);
        return (cmds);
}