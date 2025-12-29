#include <node_api.h>

// Platform and architecture detection
#if defined(_M_X64) || defined(_M_IX86) || defined(__x86_64__) || defined(__i386__)
  #define IS_X86 1
#else
  #define IS_X86 0
#endif

#if IS_X86
  #if defined(_MSC_VER)
    // Windows MSVC
    #include <intrin.h>
    static const char* get_avx_support(void) {
      int cpuInfo[4];
      __cpuid(cpuInfo, 1);
      // Check AVX (bit 28 of ECX)
      int hasAvx = (cpuInfo[2] & (1 << 28)) != 0;
      // Check OSXSAVE (bit 27 of ECX) - needed to verify OS supports AVX
      int hasOsxsave = (cpuInfo[2] & (1 << 27)) != 0;
      if (hasAvx && hasOsxsave) {
        // Check for AVX2: need to call cpuid with EAX=7, ECX=0
        __cpuidex(cpuInfo, 7, 0);
        // AVX2 is bit 5 of EBX
        if ((cpuInfo[1] & (1 << 5)) != 0) {
          return "avx2";
        }
        return "avx";
      }
      return "none";
    }
  #else
    // GCC/Clang on x86
    static const char* get_avx_support(void) {
      __builtin_cpu_init();
      if (__builtin_cpu_supports("avx2")) {
        return "avx2";
      } else if (__builtin_cpu_supports("avx")) {
        return "avx";
      }
      return "none";
    }
  #endif
#else
  // Non-x86 platforms (ARM, etc.) - AVX doesn't exist
  static const char* get_avx_support(void) {
    return "none";
  }
#endif

static napi_value DetectAvx(napi_env env, napi_callback_info info) {
  napi_value result;
  const char* avx_support = get_avx_support();
  napi_create_string_utf8(env, avx_support, NAPI_AUTO_LENGTH, &result);
  return result;
}

static napi_value Init(napi_env env, napi_value exports) {
  napi_value fn;
  napi_create_function(env, NULL, 0, DetectAvx, NULL, &fn);
  napi_set_named_property(env, exports, "detectAvx", fn);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
