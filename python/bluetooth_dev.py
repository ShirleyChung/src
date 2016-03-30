import bluetooth

target_addr = None

nearby_dev = bluetooth.discover_devices()

for bdaddr in nearby_dev:
	print bdaddr
	