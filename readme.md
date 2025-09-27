
# PARSING

1. LEXER (analyse lexicale): 
objectif : passer d'une liste de caracteres,  à une liste de tokens typé et structuré.

pour cela, determiner le type,
gestion des operateurs : 
Reconnaît >> (append), << (heredoc), | (pipe)
Différencie > de >>
,analyse lexical -> ligne en liste de token (struct token type, structe token)
 expend variable out : nouvelle ligne totalement expand
gestion des operteurs multi-caractères (>>, <<, |)
          - Gestion des heredoc(<<,>>) (delimiteur, contenue)


2.PARSER : 
transformer la liste de token en structure de commandes executables (AST - Abstract syntac Tree)

gestion des quotes,
Détecte les zones quotées,
Préserve les espaces dans les guillemets,
Différencie simple/double guillemets pour l'expansion,


etape 1: construction de commandes

creer des structures t_cmd avec 
Nom de la commande
Tableau d'arguments
Redirections associées

etape 2 : gestion des pipelines:
pouvoir creer une nouvelle structure de commande à chaque pipeline rencontré.

etape 3 : liste de token en liste de commande, construire l'AST de commandes

//exemple :
// Commande 1
cmd1->name = "echo"
cmd1->args = ["echo", "Hello john", NULL]  // $USER expandé
cmd1->redirs = NULL
cmd1->next = cmd2

// Commande 2  
cmd2->name = "grep"
cmd2->args = ["grep", "/home/john", NULL]  // $HOME expandé
cmd2->redirs = [R_OUT_TRUNC, "file.txt", NULL]
cmd2->next = NULL


LEXER	   doit :       
Découpe la chaîne
Gère les guillemets	
Détecte les opérateurs	
Classifie les tokens	
Input : Chaîne brute
Output : Liste de tokens	

PARSER doit :
Structure les commandes
Expande les variables
Construit les pipelines
Organise les redirections
Input : Liste de tokens
Output : AST de commandes


Ligne de commande: echo "Hello $USER" > "file.txt"
                    ↓
1. TOKENISATION:   [echo] ["Hello $USER"] [>] ["file.txt"]
                    ↓
2. EXPANSION:      [echo] ["Hello john"] [>] ["file.txt"]
                    ↓  
3. SUPPRESSION     [echo] [Hello john] [>] [file.txt]
   DES GUILLEMETS:
                    ↓
4. CONSTRUCTION    cmd->name = "echo"
   DE LA COMMANDE: cmd->args = ["echo", "Hello john"]
                   redirection: output -> "file.txt"
