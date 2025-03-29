import os
import sys
import subprocess
import shutil
import argparse

# Ensure tqdm is installed
try:
    from tqdm import tqdm  # Import tqdm for progress bar
except ImportError:
    print("tqdm not found. Installing...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "tqdm"])
    from tqdm import tqdm  # Import again after installation

def main():
    parser = argparse.ArgumentParser(description="File copy script")
    
    parser.add_argument(
        "--file-list",
        required=True,
        help="Path to the file containing the list of files to copy (one path per line)"
    )
    
    parser.add_argument(
        "--destination",
        required=True,
        help="Path to the destination folder"
    )
    
    args = parser.parse_args()
    
    if not os.path.exists(args.file_list):
        print(f"Error: File with paths '{args.file_list}' not found")
        sys.exit(1)
    
    # Read the list of files from the file
    try:
        with open(args.file_list, 'r') as f:
            files_to_copy = [line.strip() for line in f if line.strip()]
    except Exception as e:
        print(f"Error reading file '{args.file_list}': {str(e)}")
        sys.exit(1)
    
    # Check the destination folder
    destination = os.path.abspath(args.destination)
    
    # Create the destination folder if it doesn't exist
    os.makedirs(destination, exist_ok=True)
    print(f"Destination folder: {destination}")
    
    # Copy files with progress bar
    for file_path in tqdm(files_to_copy, desc="Copying files", unit="file"):
        if not os.path.exists(file_path):
            print(f"Warning: File {file_path} not found. Skipping")
            continue
        
        try:
            shutil.copy(file_path, destination)
        except Exception as e:
            print(f"Error copying '{file_path}': {str(e)}")

if __name__ == "__main__":
    main()
