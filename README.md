# pipex
Program that simulates the pipes in the shell. Projet for 42 Lausanne common core

## Compilation

The project includes a modular Makefile with the following rules:

- `make` or `make all` - Compiles the project
- `make clean` - Removes object files
- `make fclean` - Removes object files and executable
- `make re` - Recompiles the project from scratch
- `make bonus` - Compiles the bonus part (when bonus files are implemented)

## Makefile Structure

The Makefile is organized into clear sections for easy modification:

### Variables
- **Compiler settings**: CC, CFLAGS
- **Directories**: SRC_DIR, OBJ_DIR, INC_DIR
- **Source files**: SRC_FILES (for mandatory), BONUS_FILES (for bonus)

### How to Add New Files

**For mandatory files:**
Add the filename to the `SRC_FILES` variable in the Makefile:
```makefile
SRC_FILES	= main.c \
			  pipex.c \
			  utils.c \
			  your_new_file.c
```

**For bonus files:**
Add the filename to the `BONUS_FILES` variable:
```makefile
BONUS_FILES	= main_bonus.c \
			  pipex_bonus.c \
			  utils_bonus.c \
			  your_bonus_file.c
```

The Makefile will automatically handle compilation and linking.
