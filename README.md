# minishell

## Description
A custom shell implementation inspired by bash. This project recreates a command-line interface with basic shell functionality, built as part of the 42 curriculum. It provides command execution, environment variable management, and basic shell operations.

## Features

### Command Processing
- Command history
- Command line editing
- Input/output redirection (`<`, `>`, `>>`)
- Pipes (`|`)
- Environment variable expansion (`$VAR`)
- Signal handling (ctrl-C, ctrl-D, ctrl-\\)

### Built-in Commands
- `echo` with -n flag
- `cd` with relative/absolute paths
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Shell Features
- Working directory management
- Environment variable handling
- Exit status management (`$?`)
- Quote handling (single and double)
- Wildcard pattern matching (`*`)

## Getting Started

### Prerequisites
```bash
# On Ubuntu/Debian
sudo apt-get install readline-dev

# On macOS with Homebrew
brew install readline
```

### Installation
Clone and compile the project:
```bash
git clone https://github.com/Evan-Edwards/minishell.git
cd minishell
make
```

### Usage
Launch the shell:
```bash
./minishell
```

## Technical Details

### Parser
- Lexical analysis
- Syntax validation
- Command splitting
- Quote handling
- Variable expansion

### Executor
- Command execution
- Path resolution
- Redirection handling
- Pipe implementation
- Process management

### Built-ins Implementation
- Directory navigation
- Environment management
- Shell variable handling
- Exit status management

## Error Handling
- Syntax errors
- Command not found
- Permission denied
- Memory allocation failures
- Fork failures
- Pipe errors

## Memory Management
- Proper allocation/free
- No memory leaks
- Clean process termination
- Resource cleanup

## Additional Features
- Command history navigation
- Auto-completion (if implemented)
- Custom prompt
- Error messages similar to bash
- Signal handling customization

## Testing
The shell has been tested with:
- Complex command chains
- Various edge cases
- Memory leak detection
- Error scenarios
- Signal handling cases

## Limitations
- Some advanced bash features not implemented
- Limited scripting capabilities
- Basic wildcard implementation

---
This project is part of the 42 School curriculum.