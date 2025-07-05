//===----------------------------------------------------------------------===//
// Toy CPU Register Definition
//===----------------------------------------------------------------------===//

class Register {
  string Name;
  int ID;
}

//===----------------------------------------------------------------------===//
// Toy CPU Instructions
//===----------------------------------------------------------------------===//

class Instruction {
  string Name;
  int Opcode;
  list<Register> Operands;
}

//===----------------------------------------------------------------------===//
// Register instances
//===----------------------------------------------------------------------===//

def R0 : Register {
  let Name = "R0";
  let ID = 0;
}
def R1 : Register {
  let Name = "R1";
  let ID = 1;
}
def R2 : Register {
  let Name = "R2";
  let ID = 2;
}

//===----------------------------------------------------------------------===//
// Instruction instances
//===----------------------------------------------------------------------===//

def ADD : Instruction {
  let Name = "add";
  let Opcode = 1;
  let Operands = [R0, R1];
}
def SUB : Instruction {
  let Name = "sub";
  let Opcode = 2;
  let Operands = [R1, R2];
}

