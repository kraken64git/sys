mkdir -p out/iso/boot/grub

python3 build/build.py

cp out/image.bin out/iso/boot/
cp boot/grub/grub.cfg out/iso/boot/grub/

grub-mkrescue -o out/image.iso out/iso

qemu-system-x86_64 -cdrom out/image.iso
