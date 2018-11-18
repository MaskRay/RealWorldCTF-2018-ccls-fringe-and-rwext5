lwext4 := ~/Dev/FS/lwext4
build := Release
image := bin/rwext5.img

flag0 := fs/.config/doom/modules/private/my-cc/flag.0.o
flag1 := fs/.config/doom/modules/private/my-cc/flag.1.o

all: bin/rwext5-cat $(image)

clean:
	$(RM) $(image) bin/rwext5-cat bin/rwext5-import bin/rwext5-mkfs flag-generator

test: bin/rwext5-cat $(image) flag.plain
	mkdir -p test
	bin/rwext5-cat $(image) ctf/README
	bin/rwext5-cat $(image) ctf/.config/doom/modules/private/my-cc/flag.0.o > test/flag.0.o
	bin/rwext5-cat $(image) ctf/.config/doom/modules/private/my-cc/flag.1.o > test/flag.1.o
	ld.lld test/flag.0.o test/flag.1.o -o /dev/stdout | llvm-objcopy --dump-section=.openssl_aes-128-cbc_pass:filesystem=/tmp/flag - /dev/null
	openssl enc -d -aes-128-cbc -pass pass:filesystem -in /tmp/flag | cmp - flag.plain

release: $(image)
	tar Jcf /tmp/rwext5.tar.xz --owner=0 --group=0 --transform='s,bin/,,' bin/rwext5-import bin/rwext5-mkfs $(image)

$(image): bin/rwext5-mkfs bin/rwext5-import fs/README $(flag0) $(flag1)
	#truncate -s 4m $@
	dd if=/dev/urandom of=$@ bs=1M count=4 status=none
	bin/rwext5-mkfs $@
	find fs -type f -printf '%P\n' | xargs -i bin/rwext5-import $@ fs/{} ctf/{}
	# lwext4 master checked out at $PWD/lwext4
	git --work-tree=lwext4 --git-dir=lwext4/.git ls-files | xargs -i bin/rwext5-import $@ lwext4/{} ctf/lwext4/{}

$(flag0): flag
	head -c 1000000 flag > $@
	llvm-objcopy -I binary -B powerpc:common64 $@
	llvm-objcopy --rename-section=.data=.openssl_aes-128-cbc_pass:filesystem $@
	echo empty > empty; llvm-objcopy --add-section=.turkey_for_thanksgiving=empty $@; rm empty

$(flag1): flag
	tail -c +1000001 flag > $@
	llvm-objcopy -I binary -B powerpc:common64 $@
	llvm-objcopy --rename-section=.data=.openssl_aes-128-cbc_pass:filesystem $@
	echo empty > empty; llvm-objcopy --add-section=.gift_for_christmas=empty $@; rm empty

flag: flag.plain
	openssl enc -aes-128-cbc -pass pass:filesystem -in $< -out $@

flag.plain: flag-generator | fs
	./flag-generator > $@

bin/%: $(lwext4)/$(build)/fs_test/% | bin
	llvm-strip $< -o $@

bin fs:
	mkdir $@

flag-generator: flag-generator.cc

.PHONY: all clean test release
