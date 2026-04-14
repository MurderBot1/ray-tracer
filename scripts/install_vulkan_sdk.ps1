$version = "1.4.341.1"
$base = "C:\VulkanSDK"   # install directly into C:\VulkanSDK

if (Test-Path $base) {
    Write-Host "Vulkan SDK $version already installed."
    exit 0
}

Write-Host "Downloading Vulkan SDK $version..."

$installer = "vulkansdk-windows-X64-$version.exe"
$url = "https://sdk.lunarg.com/sdk/download/$version/windows/$installer"

Invoke-WebRequest -Uri $url -OutFile $installer -ErrorAction Stop

Write-Host "Running Vulkan SDK installer..."
Start-Process -FilePath ".\$installer" -ArgumentList `
    "--accept-licenses" `
    "--default-answer" `
    "--confirm-command" `
    "install" `
    -Wait

$env:VULKAN_SDK = $base
$env:PATH = "$base\Bin;$env:PATH"

Write-Host "Vulkan SDK installed at $base"
