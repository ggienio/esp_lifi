import serial
import threading
import time

# Configuration
PORT = "COM11"
BAUD_RATE = 15000

def receive_data(ser):
    """Continuously monitors and prints incoming serial data."""
    while ser.is_open:
        try:
            if ser.in_waiting > 0:
                incoming = ser.readline().decode("utf-8", errors="ignore").strip()
                if incoming:
                    print(f"\n[RX] {incoming}\n> ", end="")
        except Exception:
            break


def main():
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

    # Start background thread to handle non-blocking reception
    reader = threading.Thread(target=receive_data, args=(ser,), daemon=True)
    reader.start()

    print("--- Serial Transceiver ---")
    print("1. Direct Input Mode")
    print("2. Continuous Transmission Mode")
    mode = input("Select mode (1 or 2): ").strip()

    try:
        if mode == "1":
            print("\nEnter message to send (Press Ctrl+C to exit):")
            while True:
                msg = input("> ")
                if msg:
                    ser.write((msg + "\n").encode("utf-8"))

        elif mode == "2":
            payload = input("Enter phrase to repeat [default: PING]: ").strip() or "PING"
            interval = float(input("Transmission interval in seconds [default: 1.0]: ") or 1.0)

            print(f"\nTransmitting '{payload}' every {interval}s. (Press Ctrl+C to stop)")
            while True:
                ser.write((payload + "\n").encode("utf-8"))
                time.sleep(interval)
        else:
            print("Invalid selection.")

    except KeyboardInterrupt:
        print("\nClosing connection.")
    finally:
        ser.close()


if __name__ == "__main__":
    main()