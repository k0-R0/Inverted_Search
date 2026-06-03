# Inverted Search Index

A high-performance C-based Inverted Index implementation using a Hash Table with Direct Chaining. This project indexes multiple text files, allowing for rapid word-based searches across the entire dataset.

## Features
- **Modular Architecture**: Separates hashing, linked list operations, and index management using an Abstract Data Type (ADT) pattern.
- **Dynamic Hash Sizing**: Automatically estimates unique word counts based on input file sizes and selects the optimal prime number for the hash table size to minimize collisions.
- **Word Cleaning**: Automatically converts words to lowercase and strips punctuation during indexing for consistent search results.
- **Detailed Metadata**: Search results provide total occurrences, file-specific counts, and exact line numbers.

## Project Structure
The project is organized into logical modules for better maintainability:

```text
.
├── src/
│   ├── common.h         # Shared data structures (Word, File, Line nodes) and enums.
│   ├── hashing.c/h      # djb2 hash algorithm and prime-finding logic.
│   ├── list_ops.c/h     # Linked list manipulation (Direct Chaining logic).
│   ├── inverted_index.c/h # Core indexing logic and search engine.
│   ├── validations.c/h  # Input file validation.
│   └── main.c           # CLI controller and user interface.
├── build/               # Generated build artifacts (created during make).
│   ├── bin/             # Final executable.
│   └── obj/             # Compiled object files.
└── makefile             # Automated build system.
```

## Technical Details

### Hash Table Optimization
To ensure **O(1)** average search time, the system:
1. Calculates the total size of all input files.
2. Estimates unique words using the heuristic: `(Total Size / 8) * 1.3`.
3. Selects the closest prime number from a hardcoded list to define the table size, further reducing clustering and collisions.

### Direct Chaining
Collisions are handled using direct chaining. Each bucket in the hash table points to a linked list of `Word_node` structures. Each word node contains its own linked list of `File_node` structures, which in turn track occurrences via a `Line_node` list.

## Getting Started

### Prerequisites
- GCC Compiler
- GNU Make

### Building the Project
To compile the project and create the directory structure:
```bash
make
```

To remove all build artifacts:
```bash
make clean
```

### Usage
Run the binary and provide any number of `.txt` files as arguments:
```bash
./build/bin/inverted_index file1.txt file2.txt
```

Once running, you can:
1. **Display Index**: View the entire hash table.
2. **Search Word**: Query a specific word to see its frequency and location.
3. **Exit**: Gracefully close the application.

## Testing
Two sample files are included for quick verification:
- `file1.txt`
- `file2.txt`
