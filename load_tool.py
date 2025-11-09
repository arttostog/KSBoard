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
            device.write(b'\x08\x00\x00\x00')
            device.write(len(bytes_to_write).to_bytes(4))
            device.write(bytes_to_write[::-1])
            
            device.write(b'\x52')
            device.write(b'\x08\x00\x00\x00')

        except Exception as exception:
            print(f"Возникло исключение: {exception}")

    
    def read_file(path_to_file: str) -> bytes:
        with open(path_to_file, "rb") as file:
            return file.read()

    # def format_value(value: int) -> bytes:
    #     return value.to_bytes(4, byteorder='little')

if __name__ == "__main__":
    if len(argv) != 3:
        print("Слишком мало или слишком много аргументов!")
        exit(1)
    LoadTool.start(argv[1], argv[2])