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
	

class TestCase(unittest.TestCase):
	def setUpClass():
		compile()

	def _test(self, in_bytes: bytes, expected_out_bytes: bytes, buf_len: int):
		actual_out_bytes = get_result(
			in_bytes, 
			[str(buf_len)],
		)
		self.assertEqual(expected_out_bytes, actual_out_bytes)

	def test_empty(self):
		self._test(b'', b'', 2) 
		self._test(b'', b'', 3) 


	def test_empty_newlines(self):
		self._test(b'\n', b'\n', 2)
		self._test(b'\n', b'\n', 3)
		

	def test_single_line_no_nl(self):
		self._test(b'012', b'0', 2)
		self._test(b'012', b'01', 3)
		self._test(b'012', b'012', 4)
		self._test(b'012', b'012', 5)


	def test_single_line_with_nl(self):
		self._test(b'012\n', b'\n', 2)
		self._test(b'012\n', b'0\n', 3)
		self._test(b'012\n', b'01\n', 4)
		self._test(b'012\n', b'012\n', 5)
		self._test(b'012\n', b'012\n', 6)

	def test_multiline_blanks(self):
		self._test(b'\n\n', b'\n\n', 2)
		self._test(b'\n\n', b'\n\n', 3)
		self._test(b'\n\n\n', b'\n\n\n', 2)
		self._test(b'\n\n\n', b'\n\n\n', 3)

	def test_multiline_blanks(self):
		self._test(b'\n\n', b'\n\n', 2)
		self._test(b'\n\n', b'\n\n', 3)
		self._test(b'\n\n\n', b'\n\n\n', 2)
		self._test(b'\n\n\n', b'\n\n\n', 3)
		

	def test_multiline_content(self):
		self._test(b'012\n\n', b'\n\n', 2)
		self._test(b'012\n345', b'0\n34', 3)
		self._test(b'012\n345\n', b'0\n3\n', 3)
