import { createRequire } from "node:module";
import path from "node:path";
import { fileURLToPath } from "node:url";

const require = createRequire(import.meta.url);
const __dirname = path.dirname(fileURLToPath(import.meta.url));

interface NativeAddon {
  detectAvx(): "avx2" | "avx" | "none";
}

// Load the native addon using node-gyp-build
const addon: NativeAddon = require("node-gyp-build")(
  path.join(__dirname, "..")
);

/**
 * Detects AVX instruction set support on the current CPU.
 * @returns The highest supported AVX version: 'avx2', 'avx', or 'none'
 */
export default function detectAvx(): "avx2" | "avx" | "none" {
  return addon.detectAvx();
}
