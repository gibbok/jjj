# jjj

`jjj` is a minimal and fast command-line file lister with Vim key bindings.

`jjj` can be use to navigated your OS and pipe a selected file to other Linux utilities.

Usage examples:

```shell
`jjj . | less`

`jjj . | xargs open`
```

## Key binding

| Key   | Description                                 |
| ----- | ------------------------------------------- |
| j     | Move cursor down                            |
| k     | Move cursor up                              |
| h     | Visit parent folder                         |
| l     | If directory, visit it, otherwis do nothing |
| q     | Exit returning path                         |
| enter | Exit returning path                         |
| r     | Update view of the current folder           |

*Notes: you can also navigate using the arrow keys.*

## For development

Clone the repository and install dependencies:
```shell
git clone https://github.com/gibbok/jjj.git
brew install ncurses
cd ./jjj
```

Compile and run on macOS:

```shell
make dev 
```
