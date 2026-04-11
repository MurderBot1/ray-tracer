#!/usr/bin/env bash

set -e

VERSION="1.4.341.1"
BASE="$HOME/VulkanSDK/$VERSION"

if [ -d "$BASE" ]; then
    echo "Vulkan SDK $VERSION already installed."
    exit 0
fi

mkdir -p "$HOME/VulkanSDK"
cd "$HOME/VulkanSDK"

OS=$(uname -s)

if [ "$OS" = "Linux" ]; then
    FILE="vulkansdk-linux-x86_64-$VERSION.tar.gz"
    URL="https://sdk.lunarg.com/sdk/download/$VERSION/linux/$FILE?Human=true"
elif [ "$OS" = "Darwin" ]; then
    FILE="vulkansdk-macos-$VERSION.dmg"
    URL="https://sdk.lunarg.com/sdk/download/$VERSION/mac/$FILE?Human=true"
else
    echo "Unsupported OS: $OS"
    exit 1
fi

echo "Downloading Vulkan SDK $VERSION for $OS..."
curl -L "$URL" -o "$FILE"

if [ "$OS" = "Linux" ]; then
    tar -xzf "$FILE"
elif [ "$OS" = "Darwin" ]; then
    hdiutil attach "$FILE"
    cp -R /Volumes/vulkansdk-macos-$VERSION "$BASE"
    hdiutil detach /Volumes/vulkansdk-macos-$VERSION
fi

echo "export VULKAN_SDK=\"$BASE\"" >> ~/.bashrc
echo "export PATH=\"\$VULKAN_SDK/bin:\$PATH\"" >> ~/.bashrc
echo "export DYLD_LIBRARY_PATH=\"\$VULKAN_SDK/lib:\$DYLD_LIBRARY_PATH\"" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=\"\$VULKAN_SDK/lib:\$LD_LIBRARY_PATH\"" >> ~/.bashrc

echo "Vulkan SDK installed at $BASE"
