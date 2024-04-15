// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220dd5c109989a455258ad48f8a4b565086d21496859749af46245bfd505d7fb17564736f6c63430008140033

// 3 sections
// 1. contract creation code
// 2. runtime code
// 3. metadata

---
// 0x40 free memory pointer



PUSH1 0x80
PUSH1 0x40
MSTORE

// 1. create code
CALLVALUE // [msg.value]
DUP1    // [msg.value, msg.value]
ISZERO  // [msg.value == 0, msg.value]
PUSH1 0x0e  // [0x0E, msg.value == 0, msg.value]
JUMPI   // [msg.value]

PUSH0   // [0x00, msg.value]
DUP1    // [0x00,  0x00, msg.value]
REVERT  // []

// if msg.value == 0 start here 
// continue !
JUMPDEST    // [msg.value]
POP         // []
PUSH1 0xa5  // [0xA5]
DUP1        // [0xA5, 0xA5]
PUSH2 0x001b    // [0x001b, 0xA5, 0xA5]
PUSH0           // [0x00, 0x001b, 0xA5, 0xA5]
CODECOPY        // [0xa5]   Memory: [Runtime Code]

PUSH0       // [0x00, 0xA5]
RETURN      //[]
INVALID     // []


// 2. runtime code .
// entry point of all calls

// free memory pointer is 0x40
PUSH1 0x80
PUSH1 0x40
MSTORE

// msg.value check
CALLVALUE   // [msg.value]
DUP1        // [msg.value, msg.value]
ISZERO      // [msg.value == 0, msg.value]
PUSH1 0x0e  // [0x0E, msg.value == 0, msg.value]
JUMPI       // [msg.value]
PUSH0       // [0x00, msg.value]
DUP1        // [0x00,  0x00, msg.value]
REVERT      // [msg.value]

// if msg.value == 0 start here
JUMPDEST    // [msg.value]
POP         // []
PUSH1 0x04  // [0x04]
CALLDATASIZE // [calldata_size, 0x04]
LT              // [calldata_size < 0x04]
PUSH1 0x30      // [0x30, calldata_size < 0x04]
JUMPI           // []
// if calldata_size < 0x04, jump to 0x30

PUSH0           // [0x00]
CALLDATALOAD    // [CALLDATA_32BYTES]
PUSH1 0xe0      // [0xE0, 32 bytes of calldata ]
SHR             // [calldata[0:4]  ]
DUP1            // [func_selector]
PUSH4 0xcdfead2e    // [0xcdfead2e, func_selector, func_selector]
EQ              // [0xcdfead2e == func_selector, func_selector]
PUSH1 0x34      // [0x34, 0xcdfead2e == func_selector, func_selector]
JUMPI           // [func_selector]


DUP1            // [func_selector]
PUSH4 0xe026c017    // [0xe026c017, func_selector, func_selector]
EQ              // [0xe026c017 == func_selector, func_selector]
PUSH1 0x45      // [0x45, 0xe026c017 == func_selector, func_selector]
JUMPI           // [func_selector]

// if not find any function selector, revert
JUMPDEST        // []
PUSH0           // [0]
DUP1            // [0, 0]
REVERT          // []

// updateHorseNumber jump dest

JUMPDEST        // [func_selector]
PUSH1 0x43      // [0x43, func_selector]
PUSH1 0x3f      // [0x3f, 0x43, func_selector]
CALLDATASIZE    // [calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x04      // [0x43, func_selector]
PUSH1 0x59      // [0x59, 0x43, func_selector]
JUMP            // [0x04, calldata_size, 0x3f, 0x43, func_selector]

// updateNumberOfHorses jump dest 2
JUMPDEST        // [CALLDATA[4:], 0x43, func_selector]
PUSH0           // [0x00, CALLDATA[4:], 0x43, func_selector]
SSTORE          // [0x43, func_selector]
JUMP            // [func_selector]

// jump dest 5
JUMPDEST
STOP

// readHorseNumber jump dest 
JUMPDEST    // [function_selector]
PUSH0       // [0x00, function_selector]
SLOAD       // [number_of_horses, function_selector]
PUSH1 0x40  // [0x40, number_of_horses, function_selector]
MLOAD       // [0x80, number_of_horses, function_selector]
SWAP1       // [number_of_horses, 0x80, function_selector]
DUP2        // [0x80, number_of_horses, 0x80, function_selector]
MSTORE      // [0x80, function_selector]
PUSH1 0x20  // [0x20, 0x80, function_selector]
ADD         // [0xa0, function_selector]
PUSH1 0x40  // [0x40, 0xa0, function_selector]
MLOAD       // [0x80, 0xa0, function_selector]
DUP1        // [0x80, 0x80, 0xa0, function_selector]
SWAP2       // [0xa0, 0x80, 0x80, function_selector]
SUB         // [0x20, 0x80, function_selector]
SWAP1       // [0x80, 0x20, function_selector]
RETURN      // [function_selector]

// updateHorseNumber jump dest 2
JUMPDEST    // [0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH0       // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x20  // [0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP3        // [0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP5        // [calldata_size, 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
SUB         // [calldata_size - 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
SLT         // [(calldata_size - 0x04) < 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
ISZERO      // [((calldata_size - 0x04) < 0x20) == 0, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x68  // [0x68, ((calldata_size - 0x04) < 0x20) == 0, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
JUMPI       // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// we are going to jump to jump dest3 if there is more call

// revert if there isn't enough data
PUSH0       //[0x00, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP1        // [0x00, 0x00, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
REVERT      // []


JUMPDEST    // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
POP         // [0x04, calldata_size, 0x3f, 0x43, func_selector]
CALLDATALOAD    // [CALLDATA_32BYTES[4:], calldata_size, 0x3f, 0x43, func_selector]
SWAP2       //[0x3f, calldata_size, CALLDATA_32BYTES[4:], 0x43, func_selector]
SWAP1       // [calldata_size, 0x3f, CALLDATA_32BYTES[4:], 0x43, func_selector]
POP         // [0x3f, CALLDATA_32BYTES[4:], 0x43, func_selector]
JUMP        // [CALLDATA[4:], 0x43, func_selector]
INVALID

// metadata
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
TLOAD
LT
SWAP10
DUP10
LOG4
SSTORE
INVALID
DUP11
INVALID
DUP16
DUP11
INVALID
JUMP
POP
DUP7
INVALID
EQ
SWAP7
DUP6
SWAP8
BLOBHASH
INVALID
CHAINID
INVALID
JUMPDEST
REVERT
POP
TSTORE
PUSH32 0xb17564736f6c63430008140033