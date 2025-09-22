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
	echo "Cleaned output folder"
fi

echo -e "\nStarting compilation for $DEVICE...\n"
make -j$(nproc) \
    O=out KCFLAGS="-O2 -march=armv8.2-a+crypto+fp16+dotprod -mcpu=cortex-a78 -mtune=cortex-a78" \
    ARCH=arm64 \
    LLVM=1 \
    LLVM_IAS=1 \
    CROSS_COMPILE=aarch64-linux-gnu- \
    CROSS_COMPILE_ARM32=arm-linux-gnueabi- \
    moonwake_defconfig

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
	echo -e "\nCompilation failed!"
	exit 1
fi

echo -e "\nKernel compiled successfully! Zipping up...\n"

if [ -d "$AK3_DIR" ]; then
	cp -r $AK3_DIR AnyKernel3
else
	if ! git clone -q https://github.com/kernel-build-from-rainyland/AnyKernel3 -b ruby AnyKernel3; then
		echo -e "\nAnyKernel3 repo not found locally and couldn't clone from GitHub! Aborting..."
		exit 1
	fi
fi

cp $kernel AnyKernel3
cd AnyKernel3
zip -r9 "../$ZIPNAME" * -x .git
cd ..
rm -rf AnyKernel3
echo -e "\nCompleted in $((SECONDS / 60)) minute(s) and $((SECONDS % 60)) second(s) !"
echo "Zip: $ZIPNAME"

if test -z "$(git rev-parse --show-cdup 2>/dev/null)" &&
   head=$(git rev-parse --verify HEAD 2>/dev/null); then
	HASH="$(echo $head | cut -c1-8)"
fi

telegram -f $ZIPNAME -M "Completed in $((SECONDS / 60)) minute(s) and $((SECONDS % 60)) second(s) ! Latest commit: $HASH"