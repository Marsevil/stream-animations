extends Node
class_name SignalPrinter


func print_signal(message: String):
	print(message) 


func print_node_entered(params: Node, message: String):
	print(message)
	print(params.has_method("start_animation"))
	print(params.has_signal("animation_ended"))
