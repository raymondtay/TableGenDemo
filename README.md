# Toy TableGen Example

This repo demonstrates:

✅ TableGen `.td` with instructions and registers
✅ A custom TableGen backend
✅ Generation of C++ macros
✅ A simple test program

## Build & Run

```bash
./scripts/build.sh
```

## Output

Expected:

```
ADD opcode: 1
ADD operands: REG_R0, REG_R1
SUB opcode: 2
MUL opcode: 3
```

## Requirements

- LLVM with `llvm-config` and `llvm-tblgen`
- CMake >= 3.13
