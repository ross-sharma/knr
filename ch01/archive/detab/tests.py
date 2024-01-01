import unittest
import subprocess
import os
import sys


def compile():
	ret = os.system("gcc *.c")
	if ret != 0:
		raise Exception("Failed to compile")
	print("Compiled.")


def get_result(in_bytes: bytes, args: list[str]) -> bytes:
	proc = subprocess.Popen(
		["./a.out"] + args,
		stdin=subprocess.PIPE,
		stdout=subprocess.PIPE,
		stderr=sys.stderr,
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

	def _test(self, in_bytes: bytes, expected_out_bytes: bytes, buf_len: int):
		actual_out_bytes = get_result(
			in_bytes, 
			[str(buf_len)],
		)
		self.assertEqual(expected_out_bytes, actual_out_bytes)

	def test_hello(self):
		self._test(b'', b'', 10)
		self._test(b'a', b'a', 10)
		self._test(b'a\n', b'a\n', 10)
		

