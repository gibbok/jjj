# jjj

`jjj` is a minimal and fast command-line file lister with Vim key bindings.

`jjj` can be use to navigated your OS and pipe a selected file to other Linux Utilities.

Usage examples:

`jjj . | less`

`jjj . | xargs open`

## Development

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
