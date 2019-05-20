.PHONY : usage
usage :
	@echo Type one of:
	@echo     make test_crc32

.PHONY : test_crc32
test_crc32 : test_crc32.exe ; @$<
test_crc32.exe : test_crc32.cpp ..\crc32.cpp ; $(CXX) -o$@ $^

.PHONY : clean
clean :
	@DEL test_crc32.exe 2>NUL
