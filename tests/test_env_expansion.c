#include "../incl/minishell.h"

void test_env_expansion(t_mini *mini)
{
    char *tests[] = {
        "echo $HOME",              // Basic variable
        "echo \"$HOME\"",          // Quoted variable
        "echo '$HOME'",            // Single-quoted variable (shouldn't expand)
        "echo foo$HOME",           // Variable in string
        "echo $HOME$PATH",         // Multiple variables
        "echo $NONEXISTENT",       // Non-existent variable
        "echo $?",                 // Exit status
        "echo $$",                 // Process ID
        "echo \"foo$HOME bar\"",   // Variable within quoted string
        "echo $",                  // Single dollar sign
        "echo \"$\"",              // Quoted dollar sign
        "echo $HOME_$USER",        // Variables with underscore
        "echo $1HOME",             // Variable starting with number
        NULL
    };

    printf("\n=== Environment Variable Expansion Tests ===\n\n");
    
    for (int i = 0; tests[i]; i++)
    {
        char *expanded;
        printf("Test %d:\n", i + 1);
        printf("Input:    %s\n", tests[i]);
        
        // Get the bash output for comparison
        char bash_cmd[1024];
        snprintf(bash_cmd, sizeof(bash_cmd), "bash -c '%s' 2>&1", tests[i]);
        FILE *fp = popen(bash_cmd, "r");
        char bash_output[1024] = {0};
        fgets(bash_output, sizeof(bash_output), fp);
        pclose(fp);
        // Remove trailing newline from bash output
        bash_output[strcspn(bash_output, "\n")] = 0;
        
        // Your expansion
        expanded = env_var_expansion(tests[i], mini);
        if (expanded)
        {
            printf("Your exp: %s\n", expanded);
            printf("Bash:     %s\n", bash_output);
            free(expanded);
        }
        else
            printf("Your exp: (NULL)\n");
        
        printf("\n");
    }
}

int main(int argc, char **argv, char **envp)
{
    t_mini mini;
    
    (void)argc;
    (void)argv;
	// Initialize mini structure with environment
    // You'll need to set this up according to your implementation
    mini.envp = envp;
    mini.exit_status = 0;
    mini.status = DEFAULT;
    
    test_env_expansion(&mini);
    return 0;
}
