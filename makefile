cc=arm-none-eabi
lscript=linker.ld

cflags=-mfpu=vfp -c -mcpu=arm1176jzf-s -nostartfiles -Wall
lflags=-nostartfiles -T ${lscript}

dist_dir=dist/
build_dir=build/
src_dir=src/

asm_srcs=${wildcard ${src_dir}*.s}
asm_objs=${asm_srcs:${src_dir}%.s=${build_dir}%.o}
c_srcs=${wildcard ${src_dir}*.c}
c_objs=${c_srcs:${src_dir}%.c=${build_dir}%.o}
kernel=${dist_dir}kernel.img

all: ${kernel}

${kernel}: ${asm_objs} ${c_objs}
	${cc}-ld ${lflags} ${asm_objs} ${c_objs} -o ${build_dir}kernel.elf
	${cc}-objcopy ${build_dir}kernel.elf -O binary ${dist_dir}kernel.img

${c_objs}: ${build_dir}%.o:${src_dir}%.c
	${cc}-gcc ${cflags} $^ -o $@

${asm_objs}: ${build_dir}%.o:${src_dir}%.s
	${cc}-as $^ -o $@

kernel-dump: ${kernel}
	${cc}-objdump -D ${build_dir}kernel.elf > ${build_dir}kernel.dump

clean:
	rm -f ${build_dir}*
	rm -f ${dist_dir}*

.PHONY: clean
