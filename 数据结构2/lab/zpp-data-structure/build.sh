#!/bin/bash

# 读取命令行参数
while getopts "s:" arg; do
    case $arg in
    s)
        sourceFolder=$OPTARG
        ;;
    ?)
        echo "Usage: build.sh [-s sourceFolder]"
        exit 1
        ;;
    esac
done

# 设置目标文件夹名称的前缀
targetFolderPrefix="lab"

# 构造目标文件夹的路径列表
# shellcheck disable=SC2207
targetFolders=($(find "$sourceFolder" -maxdepth 1 -type d -name "$targetFolderPrefix*"))

# 如果存在目标文件夹，则进行打包操作
if [ ${#targetFolders[@]} -gt 0 ]; then
    # 构造目标 zip 文件的路径
    zipFileName="Release.zip"
    zipFilePath="$sourceFolder/$zipFileName"

    # 遍历每个目标文件夹，获取其中除了特定文件夹和指定文件外的所有可执行文件
    executableFiles=()
    for folder in "${targetFolders[@]}"; do
        releaseFolder="$folder"
        # 排除CMakeFiles文件夹和指定文件
        while IFS= read -r -d '' file; do
            executableFiles+=("$file")
        done < <(find "$releaseFolder" -type f ! -path "$releaseFolder/CMakeFiles/*" ! -name "Makefile" ! -name "cmake_install.cmake" -print0)
    done

    # 打包所有可执行文件成 zip
    zip -j "$zipFilePath" "${executableFiles[@]}"

    echo "Archive Success, The File Path is: $zipFilePath"
else
    echo "Cannot Find Folder with '$targetFolderPrefix' Prefix"
fi
