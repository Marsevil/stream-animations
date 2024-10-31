extends Node
class_name SignalPrinter


func print_signal(message: String):
	print(message) 


func print_signal_with_params(signal_name: String, params):
	print(signal_name, params)
