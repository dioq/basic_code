# base_dir=~/Library/Android/Sdk/ndk/25.2.9519653/toolchains/llvm/prebuilt/linux-x86_64/bin
base_dir=~/Library/Android/Sdk/ndk/25.2.9519653/toolchains/llvm/prebuilt/darwin-x86_64/bin
cc=${base_dir}/aarch64-linux-android33-clang
strip=${base_dir}/llvm-strip

tracee:
	@$(cc) tracee.c -o tracee
	@$(strip) ./tracee
	@adb push ./tracee /data/local/tmp/

read:
	@$(cc) read.c -o read
	@$(strip) ./read
	@adb push ./read /data/local/tmp/

write:
	@$(cc) write.c -o write
	@$(strip) ./write
	@adb push ./write /data/local/tmp/

clean:
	@-rm -rf ./read ./write ./tracee
