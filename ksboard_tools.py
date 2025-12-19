from sys import argv
from os import remove
from pathlib import Path
from subprocess import run
from serial import Serial, PARITY_NONE, STOPBITS_ONE, EIGHTBITS

class BuildTool:
    __file_extensions: list = ["*.s", "*.c", "*.cpp"]
    __file_folders: list = ["./system/", "./program/", "./libraries/"]

    __gcc: str = "arm-none-eabi-gcc"
    __gcc_args: list = ["-Wall", "-mthumb", "-Wextra", "-ffreestanding", "-O2", "-nostartfiles", "-static", "-I./include", "-I./libraries", "-mcpu=cortex-m3", "-Tlink.ld"]

    def start(path_to_output_file: str) -> tuple[bool, Exception | None]:
        try:
            compile_command: list = [ BuildTool.__gcc, ]
            compile_command += BuildTool.__gcc_args
            compile_command += BuildTool.__find_files_to_compile()
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

            if compile_result.returncode != 0:
                raise Exception(compile_result.stderr)
            
            return True, None
        except Exception as exception:
            return False, exception
    
    def __find_files_to_compile() -> list:
        files: list = [ ]
        for folder in BuildTool.__file_folders:
            folderPath: Path = Path(folder).resolve()
            for extension in BuildTool.__file_extensions:
                for file in list(folderPath.rglob(extension)):
                    files.append(str(file))

        return files

class CleanTool:
    def start(path_to_output_file: str) -> tuple[bool, Exception | None]:
        try:
            remove(path_to_output_file)
            return True, None
        except Exception as exception:
            return False, exception

# НЕ РАБОТАЕТ
class ConnectTool:
    def __init__(self, port: str) -> None:
        return # Заглушка
        try:
            self.device: Serial = Serial(
                port=port,
                baudrate=9600,
                parity=PARITY_NONE,
                stopbits=STOPBITS_ONE,
                bytesize=EIGHTBITS,
                timeout=1,
            )

            self.device.write(b'\x0D\x0A\x3E')
        except Exception:
            raise
    
    def load(self, path_to_file: str) -> tuple[bool, Exception | None]:
        return True, None # Заглушка
        try:
            bytes_to_write: bytes = self.__read_file(path_to_file)
            bytes_to_write_remainder = len(bytes_to_write) % 4
            load_address: int = 0x08000000

            for i in range(0, len(bytes_to_write) - bytes_to_write_remainder, 4):
                self.device.write(b'\x4C')
                self.device.write(load_address.to_bytes(4, "little"))
                self.device.write(b'\x04\x00\x00\x00')
                self.device.write(bytes_to_write[i])
                self.device.write(bytes_to_write[i + 1])
                self.device.write(bytes_to_write[i + 2])
                self.device.write(bytes_to_write[i + 3])
                load_address += 4
            
            if bytes_to_write_remainder != 0:
                self.device.write(b'\x4C')
                self.device.write(load_address.to_bytes(4, "little"))
                self.device.write(bytes_to_write_remainder.to_bytes(4, "little"))
                self.device.write(bytes_to_write[-bytes_to_write_remainder:])

            return True, None
        except Exception as exception:
            return False, exception
        
    
    def __read_file(path_to_file: str) -> bytes:
        with open(path_to_file, "rb") as file:
            return file.read()
    
    def start(self) -> tuple[bool, Exception | None]:
        return True, None # Заглушка
        try:
            self.device.write(b'\x52')
            self.device.write(b'\x00\x00\x00\x08')
            return True, None
        except Exception as exception:
            return False, exception
    
    def __del__(self) -> None:
        return # Заглушка
        try:
            self.device.close()
        except Exception:
            raise

class TestTool:
    test_output_file: str = "test_ksboard.elf"

    def test_compile_tool(self) -> None:
        compile_result: tuple[bool, Exception | None] = BuildTool.start(TestTool.test_output_file)
        assert compile_result[0], compile_result[1]
    
    def test_clean_tool(self) -> None:
        clean_result: tuple[bool, Exception | None] = CleanTool.start(TestTool.test_output_file)
        assert clean_result[0], clean_result[1]

class KsboardToolsMain:
    __output_file: str = "ksboard.elf"

    __clean: str = "\033[2J\033[H"
    
    __menu: str = "KSBoardTools v0.1\n"\
                "1) Очистка\n"\
                "2) Компиляция\n"\
                "3) Подключится к устройству\n"\
                "0) Выход\n"\
                "> "
    __menu_connect: str = "KSBoardTools v0.1\n"\
                "1) Загрузка\n"\
                "2) Запуск\n"\
                "0) Выход\n"\
                "> "
    
    __com_port_question: str = "Введите номер COM порта: "
    
    __success: str = "Успешно выполнено\n"\
                "Для продолжения нажмите Enter\n"
    
    __help: str = "KSBoardTools v0.1\n"\
                "Справка по быстрым командам:\n"\
                "- help - выводит список быстрых команд утилиты\n"\
                "- clean [название файла] - удаляет файл с прошивкой под указанным или стандартным именем\n"\
                "- build [название файла] - собирает прошивку в файл с указанным или со стандартным именем\n"\
                "- load <номер COM-порта> [название файла] - загружает прошивку по указанному порту с файла с указанным или стандартным именем\n"\
                "- start <номер COM-порта> - запускает прошивку на устройстве по указанному порту"

    __clean_error: str = "Произошла ошибка при очистке: {}"
    __build_error: str = "Произошла ошибка при компиляции: {}"
    __connect_error: str = "Произошла ошибка при попытке подключения к устройству: {}"
    __load_error: str = "Произошла ошибка при загрузке: {}"
    __start_error: str = "Произошла ошибка при запуске прошивки: {}"
    __undefined_command_error: str = "Неизвестная команда"
    __too_many_arguments_error: str = "Слишком много аргументов"
    __too_few_arguments_error: str = "Слишком мало аргументов"
    
    def __tool_results_handler(tool_result: tuple[bool, Exception | None], exception_message: str, is_menu: bool) -> bool:
        if tool_result[0] == False:
            match is_menu:
                case True:
                    print(KsboardToolsMain.__clean + exception_message.format(tool_result[1]))
                    input()
                case False:
                    print(exception_message.format(tool_result[1]))
            return False
        return True

    def __show_menu() -> None:
        choice: int = -1
        while choice != 0:
            print(KsboardToolsMain.__clean + KsboardToolsMain.__menu, end="")

            choice = int(input())
            match choice:
                case 1:
                    if KsboardToolsMain.__tool_results_handler(CleanTool.start(KsboardToolsMain.__output_file), KsboardToolsMain.__clean_error, True) == False:
                        continue
                case 2:
                    if KsboardToolsMain.__tool_results_handler(BuildTool.start(KsboardToolsMain.__output_file), KsboardToolsMain.__build_error, True) == False:
                        continue
                case 3:
                    port_number: str = input(KsboardToolsMain.__clean + KsboardToolsMain.__com_port_question)
                    try:
                        KsboardToolsMain.__show_menu_connection("COM" + port_number)
                    except Exception as exception:
                        print(KsboardToolsMain.__clean + KsboardToolsMain.__connect_error.format(exception))
                        input()
                    continue
                case _:
                    continue

            print(KsboardToolsMain.__clean + KsboardToolsMain.__success, end="")
            input()
    
    def __show_menu_connection(port: str) -> None:
        try:
            connect: ConnectTool = ConnectTool(port)
        except Exception:
            raise

        choice: int = -1
        while choice != 0:
            print(KsboardToolsMain.__clean + KsboardToolsMain.__menu_connect, end="")

            choice = int(input())
            match choice:
                case 1:
                    if KsboardToolsMain.__tool_results_handler(connect.load(KsboardToolsMain.__output_file), KsboardToolsMain.__load_error, True) == False:
                        continue
                case 2:
                    if KsboardToolsMain.__tool_results_handler(connect.start(), KsboardToolsMain.__start_error, True) == False:
                        continue
                case _:
                    continue 
            
            print(KsboardToolsMain.__clean + KsboardToolsMain.__success, end="")
            input()

        try:
            del connect
        except Exception:
            raise
    
    def main() -> None:
        argc: int = len(argv)

        if argc == 1:
            KsboardToolsMain.__show_menu()
            return

        match argv[1]:
            case "clean":
                match argc:
                    case 2:
                        KsboardToolsMain.__tool_results_handler(CleanTool.start(KsboardToolsMain.__output_file), KsboardToolsMain.__clean_error, False)
                    case 3:
                        KsboardToolsMain.__tool_results_handler(CleanTool.start(argv[2]), KsboardToolsMain.__clean_error, False)
                    case _:
                        print(KsboardToolsMain.__too_many_arguments_error)
            case "build":
                match argc:
                    case 2:
                        KsboardToolsMain.__tool_results_handler(BuildTool.start(KsboardToolsMain.__output_file), KsboardToolsMain.__build_error, False)
                    case 3:
                        KsboardToolsMain.__tool_results_handler(BuildTool.start(argv[2]), KsboardToolsMain.__build_error, False)
                    case _:
                        print(KsboardToolsMain.__too_many_arguments_error)
            case "load":
                match argc:
                    case 2:
                        print(KsboardToolsMain.__too_few_arguments_error)
                    case 3:
                        try:
                            connect: ConnectTool = ConnectTool("COM" + argv[2])
                            KsboardToolsMain.__tool_results_handler(connect.load(KsboardToolsMain.__output_file), KsboardToolsMain.__load_error, False)
                        except Exception as exception:
                            print(KsboardToolsMain.__clean + KsboardToolsMain.__connect_error.format(exception))
                    case 4:
                        try:
                            connect: ConnectTool = ConnectTool("COM" + argv[2])
                            KsboardToolsMain.__tool_results_handler(connect.load(argv[3]), KsboardToolsMain.__load_error, False)
                        except Exception as exception:
                            print(KsboardToolsMain.__clean + KsboardToolsMain.__connect_error.format(exception))
                    case _:
                        print(KsboardToolsMain.__too_many_arguments_error)
            case "start":
                match argc:
                    case 2:
                        print(KsboardToolsMain.__too_few_arguments_error)
                    case 3:
                        try:
                            connect: ConnectTool = ConnectTool("COM" + argv[2])
                            KsboardToolsMain.__tool_results_handler(connect.start(), KsboardToolsMain.__start_error, False)
                        except Exception as exception:
                            print(KsboardToolsMain.__clean + KsboardToolsMain.__connect_error.format(exception))
                    case _:
                        print(KsboardToolsMain.__too_many_arguments_error)
            case "help":
                match argc:
                    case 2:
                        print(KsboardToolsMain.__help)
                    case _:
                        print(KsboardToolsMain.__too_many_arguments_error)
            case _:
                print(KsboardToolsMain.__undefined_command_error)

if __name__ == "__main__":
    KsboardToolsMain.main()