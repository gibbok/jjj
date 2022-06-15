# jjj

`jjj` is a minimal and fast command-line file lister with Vim key bindings.

`jjj` can be use to navigate swiftly your OS and pipe a selected file to other Linux utilities.

Usage examples:

Select a file and pipe it to less:

```shell
jjj . | xargs cat
```

Select a file and open it with macOS finder:

```shell
jjj /Users | xargs open
```

## Downloads

Visit the [release page](https://github.com/gibbok/jjj/releases) to download the binaries.
Change the permission of the downloaded file using `chmod +x ./jjj`.
Notes: on macOS please follow this instruction [https://support.apple.com/guide/mac-help/open-a-mac-app-from-an-unidentified-developer-mh40616/mac](Open a Mac app from an unidentified developer).

## Key binding

| Key      | Description                                 |
| -------- | ------------------------------------------- |
| j        | Move cursor down                            |
| k        | Move cursor up                              |
| h        | Visit parent folder                         |
| l        | If directory, visit it, otherwis do nothing |
| q        | Exit program                                |
| esc      | Exit program                                |
| enter    | Exit returning path                         |
| spacebar | Exit returning path                         |
| r        | Update view of the current folder           |

*Notes: you can also navigate using the arrow keys.*

## Video demo

https://user-images.githubusercontent.com/17195702/173907303-8e6af4d3-898c-40d4-845f-a6585a38a816.mov

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
