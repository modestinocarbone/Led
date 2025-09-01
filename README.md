# Light-ed: `led`

Ed is a line editor originally introduced for the Unix operating system by Ken Thompson in AT&T Bell Laboratories in 1969. Due to the lack of a real user interface and the line access to the document editing, `ed` was defined as "the most user-hostile editor ever created" by Peter H. Salus.\
So why a limited version of ed should be developed?

# What is not `led`?

- `led` is not a practical way to edit documents. In fact, it’s even less practical than `ed` ever was.
- `led` should not be used in safety-critical situations or when editing files that actually matter.
- `led` is not an imitation or faithful reimplementation of `ed` . Instead, it contains only a small subset or even a modified subset of `ed` ’s original commands.

In short:  `led` can be seen as a glorified version of `touch`.

# Commands

This is a short list of implemented commands:

| Command       | Description                            |
|---------------|----------------------------------------|
| `w <file>`    | select a target file                   |
| `,p`          | print a file                           |
| `,np`         | print a file with numbered lines       |
| `x,yp`        | print a file from line x to y          |
| `x,ynp`       | print a numbered file from line x to y |
| `x,yd`        | delete a portion of a file from line x to y          |
| `<number>`    | select a line                          |
| `p`           | print the corresponding line           |
| `a`           | append text at the corresponding line  |
| `q`           | quit                                   |

# Licence

MIT Licence : do whatever you want with this piece of software, but don’t blame me if you lose your precious files.

