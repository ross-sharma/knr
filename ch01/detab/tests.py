import unittest
import subprocess
import os

def compile():
	ret = os.system("gcc *.c")
	if ret != 0:
		raise Exception("Failed to compile")
	print("Compiled.")


def get_result(in_bytes: bytes) -> bytes:
	proc = subprocess.Popen(
		"./a.out",
		shell=True,
		stdin=subprocess.PIPE,
		stdout=subprocess.PIPE,
		stderr=subprocess.STDOUT
	)

	try:
		out, _ = proc.communicate(input=in_bytes, timeout=1)
	except subprocess.TimeoutExpired:
		proc.kill()
		raise

	if proc.returncode != 0:
		raise Exception(f"exit code was {proc.returncode}")

	return out
	

class DetabTestCase(unittest.TestCase):
	def setUpClass():
		compile()

	def test_hello(self):
		result = get_result(b"abc")
		self.assertEqual(result, b'abc')

