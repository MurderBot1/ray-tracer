$version = "1.4.341.1"
$base = "C:\VulkanSDK\$version"

if (Test-Path $base) {
    Write-Host "Vulkan SDK $version already installed."
    exit 0
}

Write-Host "Downloading Vulkan SDK $version..."
$installer = "VulkanSDK-$version-Installer.exe"
$url = "https://sdk.lunarg.com/sdk/download/$version/windows/VulkanSDK-$version-Installer.exe?Human=true"

Invoke-WebRequest -Uri $url -OutFile $installer

Write-Host "Running Vulkan SDK installer..."
Start-Process -FilePath ".\$installer" -ArgumentList `
    "--accept-licenses", `
    "--default-answer", `
    "--confirm-command", `
    "--root", "`"$base`"" `
    -Wait

$env:VULKAN_SDK = $base
$env:PATH = "$base\Bin;$env:PATH"

Write-Host "Vulkan SDK installed at $base"
