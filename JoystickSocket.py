import socket
import pyglet
import threading

UDP_IP = "127.0.0.1"  
UDP_PORT = 5005
address = (UDP_IP, UDP_PORT)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Init {UDP_IP}:{UDP_PORT}")


manager = pyglet.input.ControllerManager()
controllers = manager.get_controllers()

controller = controllers[0]
controller.open()

def send_joystick_data():
    while True:

        data = f"x:{controller.leftx}, y: {controller.lefty}"
        sock.sendto(data.encode(), address)
        print(data)

joystick_thread = threading.Thread(target=send_joystick_data)
joystick_thread.daemon = True
joystick_thread.start()
pyglet.app.run()



