#ifdef TRACY_ENABLE

#include "../../includes.h"
#include "../../patcher.h"
#include <memory>

void initTracyHooks();
int (__thiscall* CCApplication_setupVerticalSync)(CCApplication*);
int __fastcall CCApplication_setupVerticalSync_H(CCApplication* self) {
    initTracyHooks();
    int ret = CCApplication_setupVerticalSync(self);
    return ret;
}

bool (__thiscall* CCEGLView_swapBuffers)(CCEGLView*);
bool __fastcall CCEGLView_swapBuffers_H(CCEGLView* self) {
    ZoneScopedN("CCEGLView::swapBuffers");
    auto ret = CCEGLView_swapBuffers(self);
    FrameMark;
    return ret;
}

#define GD base
#define COCOS2D cocos2dBase
#define COCOS2DSYM(name) GetProcAddress(cocos2dModule, name)

#define PROFILER_HOOK(address, name, ret, callConvO, callConvH, argsO, argsH, argsC) \
ret (callConvO* TracyConcat(profilerHook_, __LINE__)##_O)argsO; \
ret callConvH TracyConcat(profilerHook_, __LINE__)##_H##argsH { \
    ZoneScopedN(#name); \
    return TracyConcat(profilerHook_, __LINE__)##_O##argsC; \
} \
inline void TracyConcat(initProfilerHook_, __LINE__)(uintptr_t GD, HMODULE cocos2dModule, uintptr_t COCOS2D) { \
    MH_CreateHook(reinterpret_cast<void*>(address), \
        reinterpret_cast<void*>(&TracyConcat(profilerHook_, __LINE__)##_H), \
        reinterpret_cast<void**>(&TracyConcat(profilerHook_, __LINE__)##_O)); \
}
#include "hooks.h"
#undef PROFILER_HOOK

#ifdef PROFILE_MEMORY

#ifdef PROFILER_MEMORY_TRACKER
std::map<uintptr_t, bool> memoryTracker;

bool trackerCheck(uintptr_t retBoundLeft, uintptr_t retBoundRight) {
    auto upperBound = memoryTracker.upper_bound(retBoundLeft);
    return upperBound == memoryTracker.end() || (upperBound->second && memoryTracker.upper_bound(retBoundRight)->second);
}
#endif

void memoryAllocated(void* memory, size_t size, const char* messageText) {
#ifdef PROFILER_MEMORY_TRACKER
    auto memoryBoundLeft = reinterpret_cast<uintptr_t>(memory);
    auto memoryBoundRight = memoryBoundLeft + size;
    if(trackerCheck(memoryBoundLeft, memoryBoundRight)) {
        memoryTracker.insert(std::pair<uintptr_t, bool>(memoryBoundLeft, true));
        memoryTracker.insert(std::pair<uintptr_t, bool>(memoryBoundRight, false));
#endif

        TracyAlloc(memory, size);
#ifdef PROFILER_MEMORY_TRACKER
    }
#ifdef MEMORY_TRACKER_MESSAGES
    else {
        TracyMessage(messageText, strlen(messageText));
    }
#endif
#endif
}

void memoryFreed(void* memory, const char* messageText) {
#ifdef PROFILER_MEMORY_TRACKER
    auto memoryCast = reinterpret_cast<uintptr_t>(memory);
    if(memoryTracker.contains(memoryCast) && memoryTracker[memoryCast]) {
        memoryTracker.erase(memoryCast);
        memoryTracker.erase(memoryTracker.upper_bound(memoryCast));
#endif

        TracyFree(memory);
#ifdef PROFILER_MEMORY_TRACKER
    }
#ifdef MEMORY_TRACKER_MESSAGES
    else {
        TracyMessage(messageText, strlen(messageText));
    }
#endif
#endif
}

void* __cdecl operatorNewHook(size_t size) {
    auto ret = operator new(size);
    memoryAllocated(ret, size, "operator_new!!");
    return ret;
}

void __cdecl operatorDeleteHook(void* memory) {
    memoryFreed(memory, "operator_delete!!");
    operator delete(memory);
}

void __cdecl operatorDeleteArrayHook(void* memory) {
    memoryFreed(memory, "operator_delete[]!!");
    operator delete[](memory);
}

void* __cdecl mallocHook(size_t size) {
    auto ret = malloc(size);
    memoryAllocated(ret, size, "malloc!!");
    return ret;
}

void* __cdecl callocHook(size_t count, size_t size) {
    auto ret = calloc(count, size);
    memoryAllocated(ret, size * count, "calloc!!");
    return ret;
}

void __cdecl freeHook(void* memory) {
    memoryFreed(memory, "free!!");
    free(memory);
}

void* __cdecl reallocHook(void* memory, size_t newSize) {
    memoryFreed(memory, "realloc!! (free)");
    auto ret = realloc(memory, newSize);
    memoryAllocated(ret, newSize, "realloc!! (alloc)");
    return ret;
}

#endif

#define PROFILER_HOOK(address, name, ret, callConvO, callConvH, argsO, argsH, argsC) TracyConcat(initProfilerHook_, __LINE__)(GD, cocos2dModule, COCOS2D);
void initTracyHooks() {
    auto GD = reinterpret_cast<uintptr_t>(GetModuleHandle(0));

    auto cocos2dModule = GetModuleHandle("libcocos2d.dll");
    auto COCOS2D = reinterpret_cast<uintptr_t>(cocos2dModule);

    // frame
    MH_CreateHook(reinterpret_cast<void*>(COCOS2D + 0xc48b0),
        reinterpret_cast<void*>(&CCEGLView_swapBuffers_H),
        reinterpret_cast<void**>(&CCEGLView_swapBuffers));

    #include "hooks.h"

#ifdef PROFILE_MEMORY
    // memory
    patch(GD + 0x2820a4, pointerToBytes(reinterpret_cast<uintptr_t>(&operatorNewHook)));
    patch(GD + 0x2820a8, pointerToBytes(reinterpret_cast<uintptr_t>(&operatorDeleteHook)));
    patch(GD + 0x282158, pointerToBytes(reinterpret_cast<uintptr_t>(&operatorDeleteArrayHook)));
    patch(COCOS2D + 0x11d2e4, pointerToBytes(reinterpret_cast<uintptr_t>(&reallocHook)));
    patch(COCOS2D + 0x11d2ec, pointerToBytes(reinterpret_cast<uintptr_t>(&callocHook)));
    patch(COCOS2D + 0x11d304, pointerToBytes(reinterpret_cast<uintptr_t>(&mallocHook)));
    patch(COCOS2D + 0x11d308, pointerToBytes(reinterpret_cast<uintptr_t>(&freeHook)));
    patch(COCOS2D + 0x11d340, pointerToBytes(reinterpret_cast<uintptr_t>(&operatorDeleteArrayHook)));
    patch(COCOS2D + 0x11d344, pointerToBytes(reinterpret_cast<uintptr_t>(&operatorDeleteHook)));
    patch(COCOS2D + 0x11d348, pointerToBytes(reinterpret_cast<uintptr_t>(&operatorNewHook)));
#endif

    MH_EnableHook(MH_ALL_HOOKS);
}

void initProfiler() {
    auto address = reinterpret_cast<uintptr_t>(GetModuleHandle("libcocos2d.dll")) + 0xc1c20;
    MH_CreateHook(reinterpret_cast<void*>(address),
        reinterpret_cast<void*>(&CCApplication_setupVerticalSync_H),
        reinterpret_cast<void**>(&CCApplication_setupVerticalSync));
    MH_EnableHook(reinterpret_cast<void*>(address));
}

#endif
