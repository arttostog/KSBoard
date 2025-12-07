from sys import argv, exit
from os import remove
from pathlib import Path
from subprocess import run
from serial import Serial, PARITY_NONE, STOPBITS_ONE, EIGHTBITS

class CompileTool:
    __file_extensions: list = ["*.s", "*.c", "*.cpp"]
    __file_folders: list = [".\\system\\", ".\\program\\", ".\\libraries\\"]

    __gcc: str = "arm-none-eabi-gcc"
    __gcc_args: list = ["-Wall", "-mthumb", "-Wextra", "-ffreestanding", "-O2", "-nostartfiles", "-static", "-I./include", "-I./libraries", "-mcpu=cortex-m3", "-Tlink.ld"]

    def start(path_to_output_file: str) -> tuple[bool, Exception | None]:
        try:
            compile_command: list = [ CompileTool.__gcc, ]
            compile_command += CompileTool.__gcc_args
            compile_command += CompileTool.__find_files_to_compile()
            compile_command += [
                "-o",
                path_to_output_file,
            ]

            compile_result = run(
                compile_command,
                capture_output=True,
                text=True,
                timeout=30,
                shell=False,
            )

            print(compile_result.stderr)

            if compile_result.returncode != 0:
                raise Exception(compile_result.stderr)
            return True, None
        except Exception as exception:
            return False, exception
    
    def __find_files_to_compile() -> list:
        files: list = [ ]
        for folder in CompileTool.__file_folders:
            folderPath: Path = Path(folder)
            for extension in CompileTool.__file_extensions:
                files += list(folderPath.rglob(extension))

        output: list = [ ]
        for file in files:
            output.append(str(file))

        return output

class CleanTool:
    def start(path_to_output_file: str) -> tuple[bool, Exception | None]:
        try:
            remove(path_to_output_file)
            return True, None
        except Exception as exception:
            return False, exception

# НЕ РАБОТАЕТ
class LoadTool:
    def start(port: str, path_to_file: str) -> tuple[bool, Exception | None]:
        try:
            bytes_to_write: bytes = LoadTool.__read_file(path_to_file)

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
            
            # ...

            return True, None
        except Exception as exception:
            return False, exception

    def __read_file(path_to_file: str) -> bytes:
        with open(path_to_file, "rb") as file:
            return file.read()

class TestTools:
    test_output_file: str = "test_ksboard.elf"

    def test_compile_tool(self) -> None:
        compile_result: tuple[bool, Exception | None] = CompileTool.start(TestTools.test_output_file)
        assert compile_result[0], compile_result[1]
    
    def test_clean_tool(self) -> None:
        clean_result: tuple[bool, Exception | None] = CleanTool.start(TestTools.test_output_file)
        assert clean_result[0], clean_result[1]

class Main:
    __output_file: str = "ksboard.elf"
    __menu: str = "\033[2J\033[H"\
                "KSBoardTools v0.1\n"\
                "1) Полный цикл (Очистка, компиляция и загрузка)\n"\
                "2) Очистка\n"\
                "3) Компиляция\n"\
                "4) Загрузка\n"\
                "0) Выход\n"\
                "> "
    __success: str = "\033[2J\033[H"\
                "Успешно выполнено\n"\
                "Для продолжения нажмите Enter\n"
    __clean_error: str = "\033[2J\033[H"\
                "Произошла ошибка при очистке: {}"
    __compile_error: str = "\033[2J\033[H"\
                "Произошла ошибка при компиляции: {}"
    __load_error: str = "\033[2J\033[H"\
                "Произошла ошибка при загрузке: {}"
    
    def start() -> None:
        choice: int = -1
        while choice != 0:
            print(Main.__menu, end="")
            choice = int(input())

            if choice == 0:
                continue

            if choice == 1 or choice == 2:
                clean_result: tuple[bool, Exception | None] = CleanTool.start(Main.__output_file)
                if clean_result[0] == False and choice == 2:
                    print(Main.__clean_error.format(clean_result[1]))
                    input()
                    continue
            
            if choice == 1 or choice == 3:
                compile_result: tuple[bool, Exception | None] = CompileTool.start(Main.__output_file)
                if compile_result[0] == False:
                    print(Main.__compile_error.format(compile_result[1]))
                    input()
                    continue

            # if choice == 1 or choice == 4:
            #     load_result: tuple[bool, Exception | None] = LoadTool.start(Main.__output_file)
            #     if load_result[0] == False:
            #         print(Main.__load_error.format(load_result[1]))
            #         input()
            #         continue

            print(Main.__success, end="")
            input()

if __name__ == "__main__":
    Main.start()