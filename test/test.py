import ctypes
import os


lib_path = os.path.join(os.path.dirname(__file__), "..", "libstack.so")
lib = ctypes.CDLL(lib_path)


class Stack(ctypes.Structure):
    pass

lib.stack_create.argtypes = [ctypes.c_size_t]
lib.stack_create.restype = ctypes.POINTER(Stack)

lib.stack_destroy.argtypes = [ctypes.POINTER(Stack)]
lib.stack_destroy.restype = None

lib.stack_push.argtypes = [ctypes.POINTER(Stack), ctypes.c_int]
lib.stack_push.restype = ctypes.c_int

lib.stack_pop.argtypes = [ctypes.POINTER(Stack), ctypes.POINTER(ctypes.c_int)]
lib.stack_pop.restype = ctypes.c_int

lib.stack_peek.argtypes = [ctypes.POINTER(Stack), ctypes.POINTER(ctypes.c_int)]
lib.stack_peek.restype = ctypes.c_int

lib.stack_is_empty.argtypes = [ctypes.POINTER(Stack)]
lib.stack_is_empty.restype = ctypes.c_int

lib.stack_is_full.argtypes = [ctypes.POINTER(Stack)]
lib.stack_is_full.restype = ctypes.c_int

lib.stack_size.argtypes = [ctypes.POINTER(Stack)]
lib.stack_size.restype = ctypes.c_size_t

lib.stack_capacity.argtypes = [ctypes.POINTER(Stack)]
lib.stack_capacity.restype = ctypes.c_size_t

# Тесты
s = lib.stack_create(2)
assert s is not None, "Create failed"

assert lib.stack_is_empty(s) == 1
assert lib.stack_push(s, 100) == 0
assert lib.stack_push(s, 200) == 0
assert lib.stack_is_full(s) == 1

val = ctypes.c_int()
assert lib.stack_peek(s, ctypes.byref(val)) == 0
assert val.value == 200

assert lib.stack_push(s, 300) == 0 
assert lib.stack_capacity(s) >= 3

assert lib.stack_pop(s, ctypes.byref(val)) == 0
assert val.value == 300
assert lib.stack_pop(s, ctypes.byref(val)) == 0
assert val.value == 200
assert lib.stack_pop(s, ctypes.byref(val)) == 0
assert val.value == 100

assert lib.stack_is_empty(s) == 1
assert lib.stack_pop(s, ctypes.byref(val)) == -2 

assert lib.stack_push(None, 5) == -1
assert lib.stack_pop(None, ctypes.byref(val)) == -1
assert lib.stack_peek(s, None) == -1

lib.stack_destroy(s)
print("All Python tests passed.")
