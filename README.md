# MoonWake

Redmi Note 12 pro 5G (ruby) kernel specify for powersave

## Features

- KernelSU patch (Can build with sukisu, ksun or ksu type root)
- SusFS patch
- BBR3 implemented
- Sync with [linux-cip](https://git.kernel.org/pub/scm/linux/kernel/git/cip/linux-cip.git/), google [kernel/common](https://android.googlesource.com/kernel/common) and [xiaomi-mediatek-devs/android_kernel_xiaomi_mt6877](https://github.com/xiaomi-mediatek-devs/android_kernel_xiaomi_mt6877) repo
- Enable some twaek for powersave but keep the performance
- ln8000 fast charge driver enabled
- Updated wireguard module
- Use google clang 19 (r530567)

## Compile guide

### Option 1: Compile and go (This way to compile my kernel directly from my source)

1. Fork [kernel-build-from-rainyland/builder-non-gki](https://github.com/kernel-build-from-rainyland/builder-non-gki) repo
2. Enable action build in Actions tab
3. Click on `Build Kernel`
4. Click on `Run workflow`
5. With `Choose a config type` option, choose it as `package`
6. With `Path to a specific config JSON file (optional). Leave blank to use all configs.`, type `xiaomi-ruby.json`
7. Click `Run workflow` green button and wait
8. Download, extract the build and flash!

If you don't know how to flash, join <https://t.me/deepinrain_playground> and type `#flash_aosp` or `#flash_miui_hyperos` (for workflow build, please extract it first)

### Option 2: Kernel Player (For advanced user that build android kernel before)

Since you (Kernel Player) know how to build, pack AK3 and flash it, I just have some notes for you
- Compile it with only google `clang-r530567 (19)`, `clang-r498229b (17.0.4)` or `clang-r487747c (17.0.2)`. Clang 18, 20, 21 or older have some issues with ln8000 driver with make CN and IN variant can't boot
- To add a feature config (eg: vendor/kernelsu.config), please check `arch/arm64/configs/vendor`, see what config you want to add and then use `make $your_args_here vendor/example.config` after using `make $your_args_here ruby_defconfig`
- Recommended using `-O2` only, `-Ofast` and `-O3` will cause some stability problems
