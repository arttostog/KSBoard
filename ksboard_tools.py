from sys import argv, exit
from os import remove
from pathlib import Path
from subprocess import run
from serial import Serial, PARITY_NONE, STOPBITS_ONE, EIGHTBITS

class CompileTool:
    file_extensions: list = ["*.s", "*.c", "*.cpp"]
    file_folders: list = [".\\system\\", ".\\program\\", ".\\libraries\\"]

    gcc: str = "arm-none-eabi-gcc"
    gcc_args: list = ["-Wall", "-mthumb", "-Wextra", "-ffreestanding", "-O2", "-nostartfiles", "-static", "-I./include", "-I./libraries", "-mcpu=cortex-m3", "-Tlink.ld"]

    def start(path_to_output_file: str) -> bool:
        try:
            compilation_command: list = [ CompileTool.gcc, ]
            compilation_command += CompileTool.gcc_args
            compilation_command += CompileTool.find_files_to_compile()
            compilation_command += [
                "-o",
                path_to_output_file,
            ]

            print(f"Compilation command: {compilation_command}")

            compilation_result = run(
                compilation_command,
                capture_output=True,
                text=True,
                timeout=30,
                shell=False,
            )

            print(compilation_result.stderr)

            if compilation_result.returncode != 0:
                raise Exception("Возвращённый код после компиляции не равен 0")
            return True
        except Exception as exception:
            print(f"Произошла ошибка при компиляции '{path_to_output_file}': {exception}")
            return False
    
    def find_files_to_compile() -> list:
        files: list = [ ]
        for folder in CompileTool.file_folders:
            folderPath: Path = Path(folder)
            for extension in CompileTool.file_extensions:
                files += list(folderPath.rglob(extension))

        output: list = [ ]
        for file in files:
            output.append(str(file))

        return output

class CleanTool:
    def start(path_to_output_file: str) -> bool:
        try:
            remove(path_to_output_file)
            print("Успешно очищенно")
            return True
        except Exception as exception:
            print(f"Произошла ошибка при очистке '{path_to_output_file}': {exception}")
            return False

# НЕ РАБОТАЕТ
class LoadTool:
    def start(port: str, path_to_file: str) -> None:
        try:
            bytes_to_write: bytes = LoadTool.read_file(path_to_file)

            device: Serial = Serial(
                port=port,
                baudrate=9600,
                parity=PARITY_NONE,
                stopbits=STOPBITS_ONE,
                bytesize=EIGHTBITS,
                timeout=1,
            )

            device.write(b'\x0D\x0A\x0E')
            device.write(b'\x4C')
            device.write(b'\x08\x00\x00\x00')
            device.write(len(bytes_to_write).to_bytes(4))
            device.write(bytes_to_write[::-1])
            
            device.write(b'\x52')
            device.write(b'\x08\x00\x00\x00')

        except Exception as exception:
            print(f"При загрузке возникло исключение: {exception}")

    def read_file(path_to_file: str) -> bytes:
        with open(path_to_file, "rb") as file:
            return file.read()

if __name__ == "__main__":
    CompileTool.start("ksboard.elf")
    CleanTool.start("ksboard.elf")
    # if len(argv) != 3:
    #     print("Слишком мало или слишком много аргументов!")
    #     exit(1)
    # LoadTool.start(argv[1], argv[2])