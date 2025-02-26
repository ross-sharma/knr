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

	def _test(self, in_bytes: bytes, expected_out_bytes: bytes, tab_size: int):
		actual_out_bytes = get_result(
			in_bytes, 
			[str(tab_size)],
		)
		self.assertEqual(expected_out_bytes, actual_out_bytes)

	def test_empty(self):
		self._test(b'', b'', 4) 

	def test_empty_newline(self):
		self._test(b'\n', b'\n', 4)

	def test_just_a_tab(self):
		self._test(b'\t', b' ', 1)
		self._test(b'\t', b'  ', 2)
		self._test(b'\t', b'   ', 3)

	def test_two_tabs(self):
		self._test(b'\t\t', b'  ', 1)
		self._test(b'\t\t', b'    ', 2)
		self._test(b'\t\t', b'      ', 3)

	def test_char_and_tab(self):
		self._test(b'a\t', b'a ', 2)
		self._test(b'a\tb', b'a b', 2)
		self._test(b'a\t', b'a  ', 3)
		self._test(b'a\tb', b'a  b', 3)

	def test_multiline_content(self):
		self._test(b'a\t\n', b'a \n', 2)
		self._test(b'a\t\nb', b'a \nb', 2)
		self._test(b'a\t\nb', b'a  \nb', 3)
		self._test(b'a\t\nb\nc', b'a  \nb\nc', 3)

	def test_chars_and_tab(self):
		self._test(b'aa\tb', b'aa  b', 4)
		self._test(b'aaa\tb', b'aaa b', 4)
		self._test(b'aaaa\tb', b'aaaa    b', 4)

