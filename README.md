# detect-avx

[![CI](https://badgen.net/github/checks/biw/detect-avx)](https://github.com/biw/detect-avx/actions)
[![npm version](https://badgen.net/npm/v/detect-avx)](https://www.npmjs.com/package/detect-avx)
[![npm downloads](https://badgen.net/npm/dt/detect-avx)](https://www.npmjs.com/package/detect-avx)

A Node.js package for detecting AVX instruction set support on x86 processors.

## Installation

```sh
yarn add detect-avx
```

## Usage

```typescript
import detectAvx from "detect-avx";

const result = detectAvx();
console.log(result); // 'avx2', 'avx', or 'none'
```

## Return Values

- `'avx2'` - CPU supports AVX2 instructions
- `'avx'` - CPU supports AVX instructions (but not AVX2)
- `'none'` - CPU does not support AVX instructions (or running on non-x86 platform like ARM)

## License

MIT
