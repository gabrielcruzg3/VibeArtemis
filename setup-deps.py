#!/usr/bin/env python3
import os
import sys
import argparse
import platform
import urllib.request
import zipfile
import shutil

ORGANIZATION = "moonlight-stream"
PREBUILT_REPO = "moonlight-qt-deps"
TAG = "v12"

ASSETS = {
    "windows-x64": ("windows", "windows-x64.zip"),
    "windows-arm64": ("windows", "windows-ARM64.zip"),
    "mac": ("mac", "macos-universal.zip"),
    "steamlink": ("steamlink", "steamlink.zip"),
}

def download_asset(subfolder, asset_name):
    target_dir = os.path.join(os.getcwd(), "libs", subfolder)
    url = f"https://github.com/{ORGANIZATION}/{PREBUILT_REPO}/releases/download/{TAG}/{asset_name}"

    os.makedirs(target_dir, exist_ok=True)
    archive_path = os.path.join(target_dir, asset_name)

    print(f"Downloading {asset_name} from {url}...")
    try:
        urllib.request.urlretrieve(url, archive_path)
    except Exception as e:
        print(f"Download failed: {e}")
        return False

    print(f"Extracting {asset_name} to libs/{subfolder}...")
    with zipfile.ZipFile(archive_path, 'r') as zip_ref:
        zip_ref.extractall(target_dir)

    os.remove(archive_path)
    print(f"Successfully deployed {asset_name}")
    return True

def main():
    parser = argparse.ArgumentParser(description="Download prebuilt dependencies for VibeArtemis")
    parser.add_argument("--windows", action="store_true", help="Download Windows x64 and ARM64 prebuilt dependencies")
    parser.add_argument("--mac", action="store_true", help="Download macOS prebuilt dependencies")
    parser.add_argument("--steamlink", action="store_true", help="Download Steam Link prebuilt dependencies")
    parser.add_argument("--all", action="store_true", help="Download all dependencies for cross-compilation")
    args = parser.parse_args()

    if args.all:
        for subfolder, asset_name in ASSETS.values():
            download_asset(subfolder, asset_name)
        return

    if args.windows:
        download_asset("windows", "windows-x64.zip")
        download_asset("windows", "windows-ARM64.zip")
        return

    if args.mac:
        download_asset("mac", "macos-universal.zip")
        return

    if args.steamlink:
        download_asset("steamlink", "steamlink.zip")
        return

    # Default: Detect host OS
    system = platform.system()
    if system == "Windows":
        download_asset("windows", "windows-x64.zip")
        download_asset("windows", "windows-ARM64.zip")
    elif system == "Darwin":
        download_asset("mac", "macos-universal.zip")
    else:
        print(f"Host OS is {system}. Run with --windows to download Windows dependencies for cross-compilation.")

if __name__ == "__main__":
    main()