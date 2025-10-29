import os, subprocess


class BuildScript:
    def __init__(self, root, include, build, linker=False, image=False):
        self.ROOT = root
        self.INCLUDE = include
        self.BUILD = build
        
        if not linker:
            self.LINKER = os.path.join(self.ROOT, "build", "linker.ld")
        if not image:
            self.IMAGE = os.path.join(self.BUILD, "image.bin")

        self.objects = []

        self.build()
    
    def compileAsm(self, src, obj):
        cmd = ["nasm", "-f", "elf32", src, "-o", obj]
        subprocess.run(cmd, check=True)
    
    def compileC(self, src, obj):
        cmd = ["gcc", "-m32", "-ffreestanding", f"-I{self.INCLUDE}", "-c", src, "-o", obj]
        subprocess.run(cmd, check=True)

    def objectGen(self, src, folder):
        obj = os.path.join(self.BUILD, folder, str(src).replace(".asm", ".o").replace(".c", ".o"))
        self.objects.append(obj)
        return obj

    def processFile(self, root, file):
        if file.endswith(".asm"):
            folder = str(root).replace(str(self.ROOT), "")
            folderPath = os.path.join(self.BUILD, folder)
            os.makedirs(folderPath, exist_ok=True)
            obj = self.objectGen(file, folder)
            self.compileAsm(os.path.join(root, file), obj)
        elif file.endswith(".c"):
            folder = str(root).replace(str(self.ROOT), "")
            os.makedirs(os.path.join(self.BUILD, folder), exist_ok=True)
            obj = self.objectGen(file, folder)
            self.compileC(os.path.join(root, file), obj)

    def link(self):
        cmd = ["ld", "-m", "elf_i386", "-T", self.LINKER, "-o", self.IMAGE]
        cmd += self.objects
        subprocess.run(cmd, check=True)

    def walk(self, path):
        for root, dirs, files in os.walk(path):
            for file in files:
                self.processFile(root, file)

    def build(self):
        self.walk(self.ROOT)
        self.link()


ROOT = r"/mnt/c/Users/Матвей/sys/"
INCLUDE = os.path.join(ROOT, "include")
BUILD = os.path.join(ROOT, "out")

builder = BuildScript(ROOT, INCLUDE, BUILD)
print("Build completed successfully.")
