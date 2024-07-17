from ctypes import cdll
import ctypes
dllLibrary=R"C:\Users\USER\Desktop\Project\Voicipher\Voicipher.so"
libObject = cdll.LoadLibrary(dllLibrary)
libObject.enqueue.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
