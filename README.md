# Mini-Redis (C++20 In-Memory Key-Value Store)

A lightwight, high-performance in-memory key-value database built with modern C++ (C++20)Designed with clean architecture, modular build systems, and automated unit testing.


---

## Features
- **In-Memory Storage:** Fast key-value operations backed by hash map indexing (O(1) complexity)
- **Interactive REPL / CLI:** Interactive command line interface with real-time feedback.
- **Case-Insensitive Commands:** Tolerant command parser supporting 'SET', 'get', 'dEl', etc.
- **Modern C++ Architecture:** Utilizes C++20 features including 'std::optional' for expressive null-handling and RAII.
- **Automated Unit Testing:** Integrated with **GoogleTest (GTest)** via CMake's `FetchContent`.

---

## Supported Commands
| Command | Arguments | Description | Example |
| :--- | :--- | :--- | :--- |
| `SET` | `<key> <value>` | Stores or updates a key-value pair | `SET user arda` |
| `GET` | `<key>` | Retrieves the value of a key | `GET user` |
| `DEL` | `<key>` | Deletes the key from memory | `DEL user` |
| `QUIT` / `EXIT` | *None* | Closes the CLI session | `QUIT` |

---

## Project Structure
```text
mini-redis/
├── CMakeLists.txt        # Build system configuration & GTest integration
├── .gitignore            # Build artifacts filter
├── README.md             # Project documentation
├── include/
│   └── kvstore.hpp       # KVStore class declaration
├── src/
│   ├── kvstore.cpp       # Core key-value store logic
│   └── main.cpp          # CLI parser and command loop
└── tests/
    └── test_kvstore.cpp  # GoogleTest unit test suite

---

## Build & Run

### Prerequisites
- CMake 3.15+
- Modern C++ Compiler supporting C++20 (MSVC, GCC, or Clang)

### 1. Build the Interactive CLI
cmake -B build
cmake --build build --target mini_redis --config Debug

Run the application:
.\build\Debug\mini_redis.exe

### 2. Build & Run Automated Tests
cmake --build build --target kvstore_tests --config Debug
.\build\Debug\kvstore_tests.exe