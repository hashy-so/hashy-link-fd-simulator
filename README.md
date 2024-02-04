This repo contains:

1. An arduino sketch `simulator_sketch` for ESP32, which takes serial input and generates signals to send -> to a Hashy Link
2. A python script `send_command.py`, which is a CLI for sending commands from your PC <-> to the simulator ESP32.

With everything connected, (your pc <-> simulator ESP32 -> Hashy Link), you can replicate the input of an actual FD.

Example usage:
`python send_command.py -C 0 -V 1 -PV 1.0` -> Sets condenser relay off, vacuum relay on, and pressure voltage to 1.0

The valid commands can be found within `send_command.py`.
