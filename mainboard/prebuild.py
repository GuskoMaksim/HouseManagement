import sys
import os
import subprocess

try:
    subprocess.run(
        [
            sys.executable,
            "copy_files.py",
            "--file-list", "files_to_copy_to_include.txt",
            "--destination", "include"
        ],
        check=True
    )
except subprocess.CalledProcessError as e:
    print(f"Error executing script: {e}")
    sys.exit(1)

try:
    subprocess.run(
        [
            sys.executable,
            "copy_files.py",
            "--file-list", "files_to_copy_to_src.txt",
            "--destination", "src"
        ],
        check=True
    )
except subprocess.CalledProcessError as e:
    print(f"Error executing script: {e}")
    sys.exit(1)
