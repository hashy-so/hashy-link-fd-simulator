import argparse
import serial #pyserial
import time

# Adjust this
SERIAL_PORT = 'COM6'

def send_command(ser, command):
    print(f"Sending command: {command}")
    ser.write((command + '\n').encode())
    time.sleep(0.1)
    while ser.inWaiting() > 0:
        response = ser.readline().decode().strip()
        print(f"Response: {response}")

def setup_cli():
    parser = argparse.ArgumentParser(description="CLI for controlling ESP32 via serial port.")
    parser.add_argument("-C", choices=['0', '1'], help="Set condenser on/off")
    parser.add_argument("-V", choices=['0', '1'], help="Set vacuum on/off")
    parser.add_argument("-H", choices=['0', '1'], help="Set heater on/off")
    parser.add_argument("-D",choices=['0', '1'], help="Set drain on/off")
    parser.add_argument("-S",choices=['0', '1'], help="Set spare on/off")
    parser.add_argument("-B", type=int, help="Send a buzzer event with the given number of falling edges")
    parser.add_argument("-TV", type=float, help="Set the thermistor2 voltage (0 to 3.3V) ex: 1.0")
    parser.add_argument("-PV", type=float, help="Set the pressure voltage (0 to 3.3V) ex: 2.5")
    return parser.parse_args()

def main():
    args = setup_cli()
    
    serial_port = 'COM6'
    baud_rate = 115200
    ser = serial.Serial(serial_port, baud_rate, timeout=1)

    try:
        for arg, value in vars(args).items():
            if value is not None:
                if arg in ['TV', 'PV']:
                    command = f"-{arg} {value:.3f}"
                else:
                    command = f"-{arg} {value}"
                send_command(ser, command)
    
    finally:
        ser.close()

if __name__ == "__main__":
    main()
