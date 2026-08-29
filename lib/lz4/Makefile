ccflags-y += -O3 \
    -DLZ4_FREESTANDING=1 \
    -DLZ4_FAST_DEC_LOOP=1

obj-$(CONFIG_LZ4_COMPRESS)   += lz4.o
obj-$(CONFIG_LZ4_DECOMPRESS) += lz4.o
obj-$(CONFIG_LZ4HC_COMPRESS) += lz4hc.o

# ARMv8 optimized LZ4
obj-$(CONFIG_ARM64) += lz4armv8/lz4accel.o
obj-$(CONFIG_ARM64) += lz4armv8/lz4armv8.o

# Override default rule: preprocess lz4armv8.s using gcc (cpp enabled)
$(obj)/lz4armv8/lz4armv8.o: $(src)/lz4armv8/lz4armv8.s
	$(CC) $(c_flags) -x assembler-with-cpp -c $< -o $@
