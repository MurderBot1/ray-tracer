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
    FILE="vulkansdk-linux-x86_64-$VERSION.tar.xz"
    URL="https://sdk.lunarg.com/sdk/download/$VERSION/linux/$FILE"
elif [ "$OS" = "Darwin" ]; then
    FILE="vulkansdk-macos-$VERSION.zip"
    URL="https://sdk.lunarg.com/sdk/download/$VERSION/mac/$FILE"
else
    echo "Unsupported OS: $OS"
    exit 1
fi

echo "Downloading Vulkan SDK $VERSION for $OS..."
curl -L "$URL" -o "$FILE"

echo "Extracting Vulkan SDK..."

if [ "$OS" = "Linux" ]; then
    tar -xf "$FILE"
elif [ "$OS" = "Darwin" ]; then
    unzip -q "$FILE"
fi

# Move extracted folder to $BASE
mv "$VERSION" "$BASE"

# Environment variables
{
    echo "export VULKAN_SDK=\"$BASE\""
    echo "export PATH=\"\$VULKAN_SDK/bin:\$PATH\""
    echo "export LD_LIBRARY_PATH=\"\$VULKAN_SDK/lib:\$LD_LIBRARY_PATH\""
    echo "export DYLD_LIBRARY_PATH=\"\$VULKAN_SDK/lib:\$DYLD_LIBRARY_PATH\""
} >> ~/.bashrc

echo "Vulkan SDK installed at $BASE"
