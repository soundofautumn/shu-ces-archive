param(
    [string]$sourceFolder = ".\"
)

# 设置目标文件夹名称的前缀
$targetFolderPrefix = "lab"

# 构造目标文件夹的路径列表
$targetFolders = Get-ChildItem $sourceFolder -Directory | Where-Object { $_.Name -like "$targetFolderPrefix*" }

# 如果存在目标文件夹，则进行打包操作
if ($targetFolders.Count -gt 0) {
    # 构造目标 zip 文件的路径
    $zipFileName = "Release.zip"
    $zipFilePath = Join-Path $sourceFolder $zipFileName

    # 遍历每个目标文件夹，获取其中的所有 exe 文件
    $exeFiles = foreach ($folder in $targetFolders) {
    $releaseFolder = Join-Path $folder.FullName "Release"
        Get-ChildItem $releaseFolder -Filter "*.exe"
    }

    # 打包所有 exe 文件成 zip
    Compress-Archive -Path $exeFiles.FullName -DestinationPath $zipFilePath

    Write-Host "Archive Success, The File Path is: $zipFilePath"
} else {
    Write-Host "Cannot Find Folder with '$targetFolderPrefix' Prefix"
}
