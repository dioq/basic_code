base_dir = /usr/local/android/sdk/ndk/20.0.5594570/toolchains/llvm/prebuilt/linux-x86_64/bin/
cc = $(base_dir)aarch64-linux-android29-clang
strip = $(base_dir)aarch64-linux-android-strip

exec = main

source = main.c

all: $(exec)
	# @$(strip) ./$(exec)
	@adb push ./$(exec) /data/local/tmp/work
	@adb shell "chmod +x /data/local/tmp/work/$(exec)"	
	
$(exec): $(source)
	@$(cc) $(source) -o $(exec)

clean:
	@-rm $(exec)
