"""Сборник утилит для сборки прошивки, очистки прошивки и подключения к устройству."""

from __future__ import annotations

from sys import argv
from logging import DEBUG, Logger, StreamHandler, getLogger
from pathlib import Path
from subprocess import CalledProcessError, run
from typing import ClassVar

from serial import EIGHTBITS, PARITY_NONE, STOPBITS_ONE, Serial, SerialException

class BuildTool:
    """Класс для сборки прошивки."""

    __file_extensions: ClassVar[list[str]] = ["*.s", "*.c", "*.cpp"]
    __file_folders: ClassVar[list[str]] = ["./system/", "./program/", "./libraries/"]

    __gcc: str = "arm-none-eabi-gcc"
    __gcc_args: ClassVar[list[str]] = [
        "-Wall",
        "-mthumb",
        "-Wextra",
        "-ffreestanding",
        "-O2",
        "-nostartfiles",
        "-static",
        "-I./include",
        "-I./libraries",
        "-mcpu=cortex-m3",
        "-Tlink.ld",
    ]

    @staticmethod
    def start(path_to_output_file: str) -> Exception | None:
        """Запускает сборку прошивки."""
        try:
            compile_command: list[str] = [ BuildTool.__gcc ]
            compile_command += BuildTool.__gcc_args
            compile_command += BuildTool.__find_files_to_compile()
            compile_command += [
                "-o",
                path_to_output_file,
            ]

            run(
                compile_command,
                capture_output=True,
                text=True,
                shell=False,
                check=True,
            )
        except CalledProcessError as exception:
            return exception
        except FileNotFoundError as exception:
            return exception

    @staticmethod
    def __find_files_to_compile() -> list[str]:
        files: list[str] = [
            str(file)
            for folder in BuildTool.__file_folders
            for extension in BuildTool.__file_extensions
            for file in Path(folder).resolve().rglob(extension)
        ]
        return files

class CleanTool:
    """Класс для очистки прошивки."""

    @staticmethod
    def start(path_to_output_file: str) -> None:
        """Запускает очистку прошивки."""
        Path.unlink(path_to_output_file, missing_ok=True)

class ConnectTool:
    """Класс для подключения к устройству."""

    def __init__(self, port: str) -> None:
        """Инициализирует объект класса ConnectTool."""
        return # Заглушка
        self.device: Serial = Serial(
            port=port,
            baudrate=9600,
            parity=PARITY_NONE,
            stopbits=STOPBITS_ONE,
            bytesize=EIGHTBITS,
            timeout=1,
        )

        self.device.write(b"\x0D\x0A\x3E")

    def load(self, path_to_file: str) -> Exception | None:
        """Загружает прошивку на устройство."""
        return None # Заглушка
        try:
            bytes_to_write: bytes = self.__read_file(path_to_file)
            bytes_to_write_remainder = len(bytes_to_write) % 4
            load_address: int = 0x08000000

            for i in range(0, len(bytes_to_write) - bytes_to_write_remainder, 4):
                self.device.write(b"\x4C")
                self.device.write(load_address.to_bytes(4, "little"))
                self.device.write(b"\x04\x00\x00\x00")
                self.device.write(bytes_to_write[i])
                self.device.write(bytes_to_write[i + 1])
                self.device.write(bytes_to_write[i + 2])
                self.device.write(bytes_to_write[i + 3])
                load_address += 4

            if bytes_to_write_remainder != 0:
                self.device.write(b"\x4C")
                self.device.write(load_address.to_bytes(4, "little"))
                self.device.write(bytes_to_write_remainder.to_bytes(4, "little"))
                self.device.write(bytes_to_write[-bytes_to_write_remainder:])

        except SerialException as exception:
            return exception

    @staticmethod
    def __read_file(path_to_file: str) -> bytes:
        with Path.open(path_to_file, "rb") as file:
            return file.read()

    def start(self) -> Exception | None:
        """Запускает прошивку на устройстве."""
        return None # Заглушка
        try:
            self.device.write(b"\x52")
            self.device.write(b"\x00\x00\x00\x08")
        except SerialException as exception:
            return exception

    def __del__(self) -> None:
        """Удаляет объект класса ConnectTool."""
        return # Заглушка
        self.device.close()

class TestTool:
    """Класс для тестирования утилиты."""

    test_output_file: str = "test_ksboard.elf"

    def test_compile_tool(self) -> None:
        """Тестирование сборки."""
        compile_result: Exception | None = BuildTool.start(TestTool.test_output_file)
        CleanTool.start(TestTool.test_output_file)
        if compile_result is not None:
            raise TypeError(compile_result)

class KsboardToolsMain:
    """Основной класс утилиты."""

    __output_file: str = "ksboard.elf"

    __clean: str = "\033[2J\033[H"

    __menu: str = (
        "KSBoardTools v0.1\n"
        "1) Очистка\n"
        "2) Компиляция\n"
        "3) Подключиться к устройству\n"
        "0) Выход"
    )
    __menu_connect: str = (
        "KSBoardTools v0.1\n"
        "1) Загрузка\n"
        "2) Запуск\n"
        "0) Выход"
    )

    __com_port_question: str = "Введите номер COM порта: "

    __success: str = (
        "Успешно выполнено\n"
        "Для продолжения нажмите Enter"
    )

    __help: str = (
        "KSBoardTools v0.1\n"
        "Справка по быстрым командам:\n"
        "- help - выводит список быстрых команд утилиты\n"
        "- clean [название файла] "
        "- удаляет файл c прошивкой под указанным или стандартным именем\n"
        "- build [название файла] "
        "- собирает прошивку в файл c указанным или co стандартным именем\n"
        "- load <номер COM-порта> [название файла] "
        "- загружает прошивку по указанному порту c файла c указанным "
        "или co стандартным именем\n"
        "- start <номер COM-порта> "
        "- запускает прошивку на устройстве по указанному порту"
    )

    __build_error: str = "Произошла ошибка при компиляции: {}"
    __connect_error: str = "Произошла ошибка при попытке подключения к устройству: {}"
    __load_error: str = "Произошла ошибка при загрузке: {}"
    __start_error: str = "Произошла ошибка при запуске прошивки: {}"
    __undefined_command_error: str = "Неизвестная команда"
    __too_many_arguments_error: str = "Слишком много аргументов"
    __too_few_arguments_error: str = "Слишком мало аргументов"

    __logger: Logger = getLogger(__name__)

    @staticmethod
    def __tool_results_handler(
        tool_result: Exception | None, exception_message: str,
    ) -> None:
        if tool_result is not None:
            KsboardToolsMain.__logger.error(exception_message.format(tool_result))

    @staticmethod
    def __tool_results_handler_menu(
        tool_result: Exception | None, exception_message: str,
    ) -> bool:
        if tool_result is None:
            return True

        KsboardToolsMain.__logger.error(
            KsboardToolsMain.__clean
            + exception_message.format(tool_result),
        )
        input()
        return False

    @staticmethod
    def __show_menu_parse_choice(choice: int) -> bool:
        match choice:
            case 1:
                CleanTool.start(KsboardToolsMain.__output_file)
                return True
            case 2:
                return KsboardToolsMain.__tool_results_handler_menu(
                    BuildTool.start(KsboardToolsMain.__output_file),
                    KsboardToolsMain.__build_error,
                )
            case 3:
                port_number: str = input(
                    KsboardToolsMain.__clean + KsboardToolsMain.__com_port_question,
                )
                try:
                    KsboardToolsMain.__show_menu_connection("COM" + port_number)
                except SerialException as exception:
                    KsboardToolsMain.__logger.error(
                        KsboardToolsMain.__clean
                        + KsboardToolsMain.__connect_error.format(exception),
                    )
                    input()
                return False
        return False

    @staticmethod
    def __show_menu() -> None:
        choice: int = -1
        while choice != 0:
            KsboardToolsMain.__logger.info(
                KsboardToolsMain.__clean
                + KsboardToolsMain.__menu,
            )

            choice = int(input())
            if not KsboardToolsMain.__show_menu_parse_choice(choice):
                continue

            KsboardToolsMain.__logger.info(
                KsboardToolsMain.__clean
                + KsboardToolsMain.__success,
            )
            input()

    @staticmethod
    def __show_menu_connection_parse_choice(connect: ConnectTool, choice: int) -> bool:
        match choice:
                case 1:
                    return KsboardToolsMain.__tool_results_handler_menu(
                        connect.load(KsboardToolsMain.__output_file),
                        KsboardToolsMain.__load_error,
                    )
                case 2:
                    return KsboardToolsMain.__tool_results_handler(
                        connect.start(), KsboardToolsMain.__start_error,
                    )
        return False

    @staticmethod
    def __show_menu_connection(port: str) -> None:
        connect: ConnectTool = ConnectTool(port)

        choice: int = -1
        while choice != 0:
            KsboardToolsMain.__logger.info(
                KsboardToolsMain.__clean
                + KsboardToolsMain.__menu_connect,
            )

            choice = int(input())
            if not KsboardToolsMain.__show_menu_connection_parse_choice(
                connect, choice,
            ):
                continue

            KsboardToolsMain.__logger.info(
                KsboardToolsMain.__clean
                + KsboardToolsMain.__success,
            )
            input()

        del connect

    @staticmethod
    def __parse_args_clean(argc: int) -> None:
        match argc:
            case 2:
                CleanTool.start(KsboardToolsMain.__output_file)
            case 3:
                CleanTool.start(argv[2])
            case _:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_many_arguments_error)

    @staticmethod
    def __parse_args_build(argc: int) -> None:
        match argc:
            case 2:
                KsboardToolsMain.__tool_results_handler(
                    BuildTool.start(KsboardToolsMain.__output_file),
                    KsboardToolsMain.__build_error,
                )
            case 3:
                KsboardToolsMain.__tool_results_handler(
                    BuildTool.start(argv[2]),
                    KsboardToolsMain.__build_error,
                )
            case _:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_many_arguments_error)

    @staticmethod
    def __parse_args_load(argc: int) -> None:
        match argc:
            case 2:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_few_arguments_error)
            case 3:
                try:
                    connect: ConnectTool = ConnectTool("COM" + argv[2])
                    KsboardToolsMain.__tool_results_handler(
                        connect.load(KsboardToolsMain.__output_file),
                        KsboardToolsMain.__load_error,
                    )
                except SerialException as exception:
                    KsboardToolsMain.__logger.error(
                        KsboardToolsMain.__clean
                        + KsboardToolsMain.__connect_error.format(exception),
                    )
            case 4:
                try:
                    connect: ConnectTool = ConnectTool("COM" + argv[2])
                    KsboardToolsMain.__tool_results_handler(
                        connect.load(argv[3]),
                        KsboardToolsMain.__load_error,
                    )
                except SerialException as exception:
                    KsboardToolsMain.__logger.error(
                        KsboardToolsMain.__clean
                        + KsboardToolsMain.__connect_error.format(exception),
                    )
            case _:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_many_arguments_error)

    @staticmethod
    def __parse_args_start(argc: int) -> None:
        match argc:
            case 2:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_few_arguments_error)
            case 3:
                try:
                    connect: ConnectTool = ConnectTool("COM" + argv[2])
                    KsboardToolsMain.__tool_results_handler(
                        connect.start(),
                        KsboardToolsMain.__start_error,
                    )
                except SerialException as exception:
                    KsboardToolsMain.__logger.error(
                        KsboardToolsMain.__clean
                        + KsboardToolsMain.__connect_error.format(exception),
                    )
            case _:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_many_arguments_error)

    @staticmethod
    def __parse_args_help(argc: int) -> None:
        match argc:
            case 2:
                KsboardToolsMain.__logger.info(KsboardToolsMain.__help)
            case _:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__too_many_arguments_error)

    @staticmethod
    def __parse_args(argc: int) -> None:
        match argv[1]:
            case "clean":
                KsboardToolsMain.__parse_args_clean(argc)
            case "build":
                KsboardToolsMain.__parse_args_build(argc)
            case "load":
                KsboardToolsMain.__parse_args_load(argc)
            case "start":
                KsboardToolsMain.__parse_args_start(argc)
            case "help":
                KsboardToolsMain.__parse_args_help(argc)
            case _:
                KsboardToolsMain.__logger.error(KsboardToolsMain.__undefined_command_error)

    @staticmethod
    def main() -> None:
        """Основной метод."""
        argc: int = len(argv)

        handler: StreamHandler = StreamHandler()
        handler.setLevel(DEBUG)

        KsboardToolsMain.__logger.setLevel(DEBUG)
        KsboardToolsMain.__logger.addHandler(handler)

        if argc == 1:
            KsboardToolsMain.__show_menu()
            return

        KsboardToolsMain.__parse_args(argc)

if __name__ == "__main__":
    KsboardToolsMain.main()
