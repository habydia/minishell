
# SIGNAL HANDLING


## Objectif
Gérer les signaux système (SIGINT, SIGQUIT) dans le minishell pour assurer un comportement cohérent avec bash.

## Architecture

### 1. CONFIGURATION DES SIGNAUX

**SIGINT (Ctrl+C)** :
- Interrompt la commande en cours
- Affiche un nouveau prompt
- Réinitialise l'état de readline
- Ne quitte PAS le shell

**SIGQUIT (Ctrl+\)** :
- Ignoré dans le shell interactif
- Pas de message affiché
- Comportement identique à bash

### 2. GESTION AVEC READLINE

```c
void handle_sigint(int sig)
{
    ft_putchar_fd('\n', 1);      // Nouvelle ligne
    rl_on_new_line();            // Prépare nouvelle ligne
    rl_replace_line("", 0);      // Efface la ligne courante
    rl_redisplay();              // Affiche nouveau prompt
    g_interrupted = 1;           // Marque l'interruption
}
```

### 3. VARIABLES GLOBALES

- `g_exit_status` : Code de sortie de la dernière commande
- `g_interrupted` : Flag d'interruption par signal


### 4. COMPORTEMENTS ATTENDUS

| Signal | Action | Résultat |
|--------|--------|----------|
| Ctrl+C | SIGINT | Nouveau prompt, pas de quit |
| Ctrl+\ | SIGQUIT | Ignoré |
| Ctrl+D | EOF | Quitte le shell |

### 6. EXEMPLE D'UTILISATION

```bash
Minishell> ls -la^C
Minishell> echo "test"^C
Minishell> ^D
exit
```

Le signal SIGINT (^C) interrompt sans quitter, EOF (^D) termine le shell.
