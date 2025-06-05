# Minishell:
It's a core part of the 42 curriculum that involves creating a simplified UNIX shell, helping students deepen their understanding of process management, parsing, signals, and environment variables in C.
The **Minishell** project that developed in C, is a simplified shell that emulates basic behavior of `bash`. It's designed to deepen understanding of:
- Processes and file descriptors
- Parsing complex input (e.g., quotes, pipes, redirections)
- Environment variables and their expansion
- Signal handling
- Built-in commands implementation

## 🚀 Features

- ✅ Prompt display and command line input
- ✅ Lexical analysis and parsing
- ✅ Word splitting and quote removal
- ✅ Environment variable expansion (`$VAR`)
- ✅ Redirections: `>`, `>>`, `<`, `<<`
- ✅ Pipes (`|`)
- ✅ Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- ✅ Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- ✅ Exit codes per POSIX standards
- ✅ Error handling and cleanup

  ## 🛠️ Technical Details

- **Language:** C
- **Tools:** `readline`, `termios`, POSIX APIs
- **Platform:** Unix/Linux (macOS and Linux compliant)

## 📦 Installation

```bash
git clone https://github.com/shahnajsc/42minishell.git
cd minishell
make
```
## 🤝 Contributors
[Shahnaj](https://github.com/shahnajsc)

[Hager](https://github.com/imhaqer)

## Project Status
Submission and peer evaluation is done. Secured 101%

![Screenshot from 2025-06-05 13-17-51](https://github.com/user-attachments/assets/1f3dbe75-55c3-4f37-addd-47e079d6ae34)


