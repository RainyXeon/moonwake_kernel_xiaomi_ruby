#!/bin/bash
#
# Compile script for kernel
#

SECONDS=0 # builtin bash timer
DEVICE="ruby"
ZIPNAME="MoonWake-Private-$(date '+%Y%m%d-%H%M').zip"

export ARCH=arm64
export KBUILD_BUILD_USER=rainyxeon
export KBUILD_BUILD_HOST=private.deepinrain.com
export PATH="/root/clang-r530567/bin/:$PATH"

if [[ $1 = "-c" || $1 = "--clean" ]]; then
	rm -rf out
	echo "[MoonWake Private Build Script] Cleaned output folder"
fi

echo "[MoonWake Private Build Script] Starting compilation for $DEVICE..."

if [[ $1 = "-mc" || $1 = "--makeconfig" || $2 = "-mc" || $2 = "--makeconfig" ]]; then
    echo "[MoonWake Private Build Script] Make config for $DEVICE"
    make -j$(nproc) \
        O=out KCFLAGS="-O2 -march=armv8.2-a+crypto+fp16+dotprod -mcpu=cortex-a78 -mtune=cortex-a78" \
        ARCH=arm64 \
        LLVM=1 \
        LLVM_IAS=1 \
        CROSS_COMPILE=aarch64-linux-gnu- \
        CROSS_COMPILE_ARM32=arm-linux-gnueabi- \
        moonwake_defconfig
fi

echo "[MoonWake Private Build Script] Starting building Image.gz-dtb for $DEVICE..."
make -j$(nproc) \
    O=out KCFLAGS="-O2 -march=armv8.2-a+crypto+fp16+dotprod -mcpu=cortex-a78 -mtune=cortex-a78" \
    ARCH=arm64 \
    LLVM=1 \
    LLVM_IAS=1 \
    CROSS_COMPILE=aarch64-linux-gnu- \
    CROSS_COMPILE_ARM32=arm-linux-gnueabi- \
    Image.gz-dtb

kernel="out/arch/arm64/boot/Image.gz-dtb"

if [ ! -f "$kernel" ]; then
	echo "[MoonWake Private Build Script] Compilation failed!"
	exit 1
fi

echo "[MoonWake Private Build Script] Kernel compiled successfully! Zipping up..."

if [ -d "$AK3_DIR" ]; then
	cp -r $AK3_DIR AnyKernel3
else
	if ! git clone -q https://github.com/kernel-build-from-rainyland/AnyKernel3 -b ruby_private AnyKernel3; then
		echo "[MoonWake Private Build Script] AnyKernel3 repo not found locally and couldn't clone from GitHub! Aborting..."
		exit 1
	fi
fi

cp $kernel AnyKernel3
cd AnyKernel3
zip -r9 "../$ZIPNAME" * -x .git
cd ..
rm -rf AnyKernel3
echo "[MoonWake Private Build Script] Completed in $((SECONDS / 60)) minute(s) and $((SECONDS % 60)) second(s) !"
echo "[MoonWake Private Build Script] Zip: $ZIPNAME"