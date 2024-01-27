<h1 align="center">
	📖 LIBFT
</h1>

<p align="center">
	<b><i>A C Library</i></b><br>
</p>

<p align="center">
    <img alt="score" src="https://img.shields.io/badge/score-125%2F100-brightgreen" />
<p align="center">
    <img alt="solo" src="https://img.shields.io/badge/solo-yellow" />
    <img alt="estimated time" src="https://img.shields.io/badge/time%20spent-70%20hours-blue" />
    <img alt="XP earned" src="https://img.shields.io/badge/XP%20earned-462-orange" />
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/lkilpela/libft?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/lkilpela/libft?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/lkilpela/libft?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/lkilpela/libft?color=green" />
</p>

## 📚 About The Project

`libft` is a custom C library created as part of the Hive Helsinki curriculum. The goal of this project is to recreate some standard C library functions and some additional utility functions that can be used in a wide range of projects.

The library includes a variety of functions, including string manipulation, memory management, character checks, and linked list operations. These functions mimic the behavior of their standard C library counterparts, providing a deeper understanding of these fundamental operations.

This library serves as a solid foundation for coding more complex projects in C, as it provides a suite of tested and reliable functions that students can use in their future projects.

This project was completed as a **solo project**.

## 🏁 Getting Started

## 🛠️ Installation & Setup

1. Clone the repository: `git clone https://github.com/lkilpela/libft.git`
2. Navigate into the project directory: `cd libft`
3. Compile the library: `make`

### 📚 Library Contents

The `libft` library contains the following functions:

#### String manipulation functions
- `ft_strcpy`
- `ft_strncpy`
- `ft_strcat`
- `ft_strncat`
- `ft_strlcat`
- `ft_strchr`
- `ft_strrchr`
- `ft_strstr`
- `ft_strnstr`
- `ft_strcmp`
- `ft_strncmp`
- `ft_atoi`
- `ft_strdup`
- `ft_strnew`
- `ft_strdel`
- `ft_strclr`
- `ft_striter`
- `ft_striteri`
- `ft_strmap`
- `ft_strmapi`
- `ft_strequ`
- `ft_strnequ`
- `ft_strsub`
- `ft_strjoin`
- `ft_strtrim`
- `ft_strsplit`
- `ft_itoa`
- `ft_putchar`
- `ft_putstr`
- `ft_putendl`
- `ft_putnbr`
- `ft_putchar_fd`
- `ft_putstr_fd`
- `ft_putendl_fd`
- `ft_putnbr_fd`

#### Memory manipulation functions
- `ft_memset`
- `ft_bzero`
- `ft_memcpy`
- `ft_memccpy`
- `ft_memmove`
- `ft_memchr`
- `ft_memcmp`
- `ft_memalloc`
- `ft_memdel`

#### Character check functions
- `ft_isalpha`
- `ft_isdigit`
- `ft_isalnum`
- `ft_isascii`
- `ft_isprint`
- `ft_toupper`
- `ft_tolower`

#### Linked list functions
- `ft_lstnew`
- `ft_lstdelone`
- `ft_lstdel`
- `ft_lstadd`
- `ft_lstiter`
- `ft_lstmap`

## 📝 Evaluation Requirements

The `libft` project was evaluated based on the following criteria:

1. **Code Quality**: The code must be clear, concise, and efficient. It should be well-organized and easy to read.

2. **Functionality**: All functions must work correctly and handle edge cases. The library should not have any memory leaks.

3. **Compiling**: The library must compile without any errors or warnings.

4. **Makefile**: The project should include a Makefile that compiles the library and includes rules like `all`, `clean`, `fclean`, and `re`.

5. **Bonus**: Bonus points were awarded for additional functions that are useful for the rest of the program.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/lkilpela/libft/blob/main/docs/LICENSE) file for details.