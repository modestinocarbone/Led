# Led, Light-ed

Ed is a line editor originally itroduced for the Unix operating system by Ken Thompson in AT&T Bell Laboratories in 1969.\
So why a limited version of ed should be developed?

# What is not Led?

- **Led** is not a practical way to edit documents. In fact, it’s even less practical than **ed** ever was.
- **Led** should not be used in safety-critical situations or when editing files that actually matter.
- **Led** is not an imitation or faithful reimplementation of **ed** . Instead, it contains only a small subset or even a modified subset of **ed** ’s original commands.

In short:  **Led** can be seen as a glorified version of **touch**.

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

MIT Licence — do whatever you want with it, but don’t blame me if you lose your precious files.

