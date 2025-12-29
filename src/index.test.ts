import { describe, it, expect } from "vitest";
import detectAvx from "./index.js";

describe("detectAvx", () => {
  it("should be callable and return a result", () => {
    const result = detectAvx();
    expect(result).toBeDefined();
  });

  it("should return a valid AVX support level", () => {
    const result = detectAvx();
    expect(["avx2", "avx", "none"]).toContain(result);
  });

  it("should return a string", () => {
    const result = detectAvx();
    expect(typeof result).toBe("string");
  });

  it("should return consistent results across multiple calls", () => {
    const result1 = detectAvx();
    const result2 = detectAvx();
    expect(result1).toBe(result2);
  });
});
