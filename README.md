# myteams

Collaborative communication with sockets implemented in C.

## Prerequisites

- Install uuid library
  On Fedora use "sudo dnf install libuuid-devel"
- Add the custom library libmyteams.so to the path with the following command.
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./libs/myteams

## How to use

- Build the Makefile at the root with the command : make
- Use "./myteams_server -help" to see how to use the server.
- Use "./myteams_cli .help" to see how to use the client.
