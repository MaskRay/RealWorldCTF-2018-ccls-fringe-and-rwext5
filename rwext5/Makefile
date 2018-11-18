lwext4 := ~/Dev/FS/lwext4
build := Release
image := /tmp/4m

all: bin/rwext5-cat bin/rwext5-import bin/rwext5-mkfs

clean:
	$(RM) $(image) bin/rwext5-cat bin/rwext5-import bin/rwext5-mkfs flag-generator

test:
	bin/rwext5-cat $(image) home/ray/flag | cmp fs/flag -

$(image): bin/rwext5-mkfs bin/rwext5-import fs/flag
	dd if=/dev/urandom of=$@ bs=1M count=4 status=none
	bin/rwext5-mkfs $@
	bin/rwext5-import $@ fs/flag ray/flag
	# lwext4 master checked out at $PWD/lwext4
	git --work-tree=lwext4 --git-dir=lwext4/.git ls-files | xargs -i bin/rwext5-import $@ lwext4/{} ray/lwext4/{}

fs/flag: fs/flag.plain
	openssl enc -aes-128-cbc -pass pass:filesystem -in $< -out $@

fs/flag.plain: flag-generator | fs
	./flag-generator > $@

bin/%: $(lwext4)/$(build)/fs_test/% | bin
	cp $< $@

bin fs:
	mkdir $@

flag-generator: flag-generator.cc

.PHONY: all clean test
