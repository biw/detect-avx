import { defineConfig, type Options } from "tsup";

export default defineConfig((options: Options) => ({
  clean: true,
  dts: true,
  entry: ["src/index.ts"],
  format: "esm",
  platform: "node",
  target: "node18",
  minify: !options.watch,
  sourcemap: true,
}));
