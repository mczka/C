# LINUX
https://kernel.org

https://github.com/0xAX/linux-insides/blob/master/SUMMARY.md

;ld exeve
http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html

# x86-64
uOPS microcode instruction

https://www.agner.org/optimize/

https://www.agner.org/optimize/microarchitecture.pdf

https://www.agner.org/optimize/optimizing_assembly.pdf

https://www.agner.org/optimize/instruction_tables.pdf


# file format ELF64, objdump, [Preprocessing, Compilation, Assembling, Linking]
https://talks.harshkapadia.me/elf/content.html

;x86-64 reset vector SIMI AP BSP 
https://binarydebt.wordpress.com/2018/10/06/how-does-an-x86-processor-boot/

# ASM assembler x86_64
https://github.com/0xAX/asm

;NASM x86_64 and examples

https://ww2.ii.uj.edu.pl/~kapela/pn/print-one-lecture.php?description=&lectureNumber=0

;Intel APX new instructions in userspace/guest the best from ARM64/RISCV and additional 16 regs "Diamond Rapids" Intel Xeon 7 / AMD EPYC zen7

https://www.intel.com/content/www/us/en/developer/articles/technical/advanced-performance-extensions-apx.html

# C language
https://github.com/wadehuber/codeexamples/tree/master/c

; new stack
https://developers.redhat.com/articles/2023/06/19/debugging-gdb-create-custom-stack-winders#building_an_example_use_case

# build linux kernel + userspace  - mother of build
https://linuxfromscratch.com

# Linux distrubution:
; AL killer feature: APKOVL/LBU, APK ; https://postmarketos.org/ alpine with glibc + systemd

https://alpinelinux.org

; DEB

https://debian.org

;RPM

https://rockylinux.org


# BIOS and bootloader
https://coreboot.org  github.com/coreboot

https://linuxboot.org github.com/linuxboot

# APP  fd.io vpp
https://github.com/FDio/vpp

https://ipng.ch/s/articles/



# UTF-8  ą, ć, ę, ł, ń, ó, ś, ź, ż
Na systemach opartych na Linuxie można sprawdzić i zmienić kodowanie plików za pomocą narzędzia iconv lub file.

Sprawdzenie kodowania pliku

file -i plik.txt

Konwersja pliku do UTF-8

iconv -f ISO-8859-2 -t UTF-8 plik.txt -o plik_utf8.txt

Warto upewnić się, że środowisko terminala obsługuje UTF-8. Można to sprawdzić poleceniem:

echo $LANG

Jeśli wynik nie wskazuje na UTF-8 (np. pl_PL.UTF-8), można ustawić odpowiednie kodowanie poprzez edycję pliku /etc/default/locale.

# GDB

bp _start _init main

run -c ../startup.conf

x/16xg addr

```
;db_ptr
x/gx $rax

x/gx *((uint64_t*)$rax)

x/s *((uint64_t*)*((uint64_t*)$rax))
```
