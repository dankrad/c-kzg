INCLUDE_DIRS = ../../src ../../blst/bindings ../../blst/src 

ckzg.dll: ckzg.c ../../min-src/c_kzg_4844.o ../../lib/libblst.a
	clang -O -Wall -shared ${addprefix -I,${INCLUDE_DIRS}} -o $@ $^

test-mac: tests.c ckzg.c ../../src/c_kzg_4844.c ../../blst/libblst.a
	cd ../../blst && ./build.sh && cd ../min-bindings/csharp
	clang -O -Wall -target arm64-darwin ${addprefix -I,${INCLUDE_DIRS}} -o ckzg $^

test-win: tests.c ckzg.c ../../src/c_kzg_4844.c ../../blst/blst.lib
#	cd ..\..\blst && build.bat && cd ..\bindings\csharp
	clang -O -w -Wall ${addprefix -I,${INCLUDE_DIRS}} $^ -o ./tests.exe

# all the platforms
#	clang -O -Wall -shared -target x86_64-linux ${addprefix -I,${INCLUDE_DIRS}} -o ./Ckzg.Bindings/runtimes/win-x64/native/ckzg.so $^
#	clang -O -Wall -shared -target arm64-linux ${addprefix -I,${INCLUDE_DIRS}} -o ./Ckzg.Bindings/runtimes/win-x64/native/ckzg.so $^
#	clang -O -Wall -shared -target arm64-darwin ${addprefix -I,${INCLUDE_DIRS}} -o ./Ckzg.Bindings/runtimes/win-x64/native/ckzg.so $^
#	clang -O -Wall -shared -target x86_64-darwin ${addprefix -I,${INCLUDE_DIRS}} -o ./Ckzg.Bindings/runtimes/win-x64/native/ckzg.so $^
#	clang -O -Wall -shared -target x86_64-win ${addprefix -I,${INCLUDE_DIRS}} -o ./Ckzg.Bindings/runtimes/win-x64/native/ckzg.so $^

	
