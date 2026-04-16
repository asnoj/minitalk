# minitalk*This project has been created as part of the 42 curriculum by jcrochet.*

<div align="center">

<h1>📡 MINITALK</h1>

**Inter-process communication using UNIX signals — bit by bit**

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norm](https://img.shields.io/badge/Norm-v3-brightgreen?style=flat-square)](https://github.com/42School/norminette)

</div>

---

## 📖 Description

**minitalk** is a 42 School project that implements a minimal communication system between two processes using only UNIX signals. A **server** waits for incoming messages, and a **client** sends them — encoding each character as a sequence of 8 bits transmitted via `SIGUSR1` and `SIGUSR2`.

The project explores low-level process communication, signal handling with `sigaction`, and bitwise operations in C.

Key concepts covered:
- UNIX signals (`SIGUSR1`, `SIGUSR2`, `SIGINT`)
- `sigaction` for reliable signal handling
- Bit-level encoding and decoding of characters
- UTF-8 character support
- Bidirectional acknowledgment between client and server

---

## ⚙️ How it works

Each character is split into 8 bits and sent one at a time:

- `SIGUSR1` → bit `0`
- `SIGUSR2` → bit `1`

```
Character 'A' = 0x41 = 01000001

Client sends:  SIGUSR1 SIGUSR2 SIGUSR1 SIGUSR1 SIGUSR1 SIGUSR1 SIGUSR1 SIGUSR2
                  0       1       0       0       0       0       0       1
```

The server reconstructs each character by shifting bits into a buffer. Once 8 bits are received, it decodes the byte. A null byte (`\0`) signals the end of the message, after which the server sends `SIGUSR1` back to the client as acknowledgment.

**Two-phase reception** — the server first receives the client's PID (sent as an ASCII string before the message), then switches to message mode. This allows the server to reply directly to the correct client process.

```
Client                          Server
  │── send PID (ASCII) ────────►│
  │── send message ─────────────►│  (reconstructs + prints)
  │◄─────────────── SIGUSR1 ────│  (acknowledgment)
```

---

## 🗂️ Files

```
minitalk/
├── sources/
│   ├── server.c          # Signal handler, bit reconstruction, PID parsing
│   ├── client.c          # Bit encoding, signal sending, ACK waiting
│   ├── utils.c           # ft_atoi, ft_itoa, get_utf8_size
│   ├── talk.h            # Shared structs, defines, prototypes
│   └── printf/           # Embedded ft_printf
│       ├── ft_printf.c   # Format parser + ft_line (line buffer)
│       ├── ft_utils.c    # putchar, putstr, putnbr, puthex
│       ├── ft_utils_2.c  # puthex_upper, putptr, ft_strdup, ft_strlen
│       └── ft_printf.h
└── Makefile
```

**Key struct:**

```c
typedef struct s_data
{
    unsigned char   curr_c;      // Byte being reconstructed
    int             bit_count;   // Bits received so far (0-7)
    pid_t           client_pid;  // Sender's PID
    int             is_pid;      // Reception phase: 1=PID, 0=message
    int             pid;         // Parsed client PID value
    size_t          charnbr;     // Characters received
} t_data;
```

---

## 🔧 Instructions

```bash
# Compile (default WAIT=700µs between signals)
make

# Compile with custom inter-signal delay
make WAIT=500

# Predefined speed presets
make test-fast    # WAIT=300µs  — fast machines
make test-normal  # WAIT=700µs  — default
make test-slow    # WAIT=1500µs — slow or loaded machines

# Clean
make clean        # Remove object files
make fclean       # Remove objects + executables
make re           # Full rebuild
```

**Running:**

```bash
# Terminal 1 — start the server (prints its PID)
./server
# Output: 12345

# Terminal 2 — send a message
./client 12345 "Hello, World!"
./client 12345 "UTF-8 works too: 🦔"
```

The server prints each message as it arrives and sends an acknowledgment back to the client. Press `Ctrl+C` on the server for a clean shutdown.

---

## 🧮 Technical Highlights

**`WAIT` is compile-time configurable** — the inter-signal delay is baked in at compilation via `-DWAIT=$(WAIT)`, making it easy to tune for different machine speeds without rewriting code.

**UTF-8 aware** — `get_utf8_size` reads the leading byte bitmask to detect multi-byte sequences (1–4 bytes), allowing the server to correctly handle emoji and non-ASCII characters sent by the client.

**`ft_line` line buffer** — instead of printing each character immediately on arrival (which produces fragmented output), characters are accumulated in a static heap buffer up to `C_NBR_MAX` (100) chars, then flushed as a complete line. This prevents partial writes from interleaving with the server's own output.

**`sigaction` over `signal`** — `sigaction` is used throughout for reliable, portable signal handling. It prevents signal handlers from being reset after each delivery and allows fine-grained control over signal masks.

---

## 📚 Resources

- [`sigaction` man page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [`kill` man page](https://man7.org/linux/man-pages/man2/kill.2.html)
- [UNIX Signals — Wikipedia](https://en.wikipedia.org/wiki/Signal_(IPC))
- [UTF-8 encoding — Wikipedia](https://en.wikipedia.org/wiki/UTF-8)
- [Bitwise operations in C — cppreference](https://en.cppreference.com/w/c/language/operator_arithmetic)

**AI usage:** AI was used exclusively for README writing and formatting. All source code was written manually without AI assistance, in compliance with the 42 AI policy for foundational projects.

---

<div align="center">

Made with ☕ at [42 LeHavre]([https://42LeHavre.fr](https://42lehavre.fr)) — **jcrochet**

</div>
