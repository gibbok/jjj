# jjj

`jjj` is a minimal and fast command-line file lister with Vim key bindings.

`jjj` can be used to navigate swiftly your OS and pipe a selected file to other Linux utilities.

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

- Visit the [release page](https://github.com/gibbok/jjj/releases) to download the binaries
- Change the permission of the downloaded file using `chmod +x ./jjj`

*Notes: on macOS please follow this instructions [Open a Mac app from an unidentified developer](https://support.apple.com/guide/mac-help/open-a-mac-app-from-an-unidentified-developer-mh40616/mac).*

## Key binding

| Key      | Description                                                     |
| -------- | --------------------------------------------------------------- |
| j        | Move cursor down                                                |
| k        | Move cursor up                                                  |
| h        | Visit parent folder                                             |
| l        | If directory, visit it, otherwis do nothing                     |
| q        | Exit program                                                    |
| esc      | Exit program                                                    |
| enter    | Exit returning path                                             |
| spacebar | Exit returning path                                             |
| r        | Update view of the current folder and reset the cursor position |

*Notes: you can also navigate using the arrow keys.*

## Video demo

https://user-images.githubusercontent.com/17195702/175805159-d82c101e-f8b2-4aae-9e8a-490b1d9ab716.mov

## For development

Clone the repository and install dependencies:

```shell
git clone https://github.com/gibbok/jjj.git
brew install ncurses
cd ./jjj
```

Compile and run on macOS:

```shell
make test-files
make dev 
```

Build for macOS and Linux using Docker:

```shell
make build-mac
make build-linux
```
