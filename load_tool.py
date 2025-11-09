from sys import argv, exit
from serial import Serial, PARITY_NONE, STOPBITS_ONE, EIGHTBITS

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
            device.write(LoadTool.format_value(0x08000000))
            device.write(LoadTool.format_value(len(bytes_to_write)))
            device.write(bytes_to_write)
            
            device.write(b'\x52')
            device.write(LoadTool.format_value(0x08000000))

        except Exception as exception:
            print(f"Возникло исключение: {exception}")

    
    def read_file(path_to_file: str) -> bytes:
        with open(path_to_file, "rb") as file:
            return file.read()

    def format_value(value: int) -> bytes:
        return value.to_bytes(4, byteorder='little')

if __name__ == "__main__":
    if len(argv) != 3:
        print("Слишком мало или слишком много аргументов!")
        exit(1)
    LoadTool.start(argv[1], argv[2])